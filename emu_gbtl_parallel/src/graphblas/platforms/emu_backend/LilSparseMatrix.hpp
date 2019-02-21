#ifndef GB_SEQUENTIAL_LILSPARSEMATRIX_HPP
#define GB_SEQUENTIAL_LILSPARSEMATRIX_HPP

#include <iostream>
#include <vector>
#include <typeinfo>
#include <tuple>
//#include <stdexcept>
#include "distributed.h"
#include "memoryweb.h"


#include <graphblas/graphblas.hpp>

//****************************************************************************

namespace GraphBLAS
{
    namespace backend
    {
        template<typename ScalarT, typename... TagsT>
        class LilSparseMatrix
        {
        public:
            typedef ScalarT ScalarType;

            // Constructor
            LilSparseMatrix(IndexType num_rows,
                            IndexType num_cols)
                : m_num_rows(num_rows),
                  m_num_cols(num_cols),
                  m_nvals(0),
                  m_num_nodelets(NODELETS()),
                  m_num_rows_per_nodelet(
                      (m_num_rows % m_num_nodelets == 0) ?
                      m_num_rows/m_num_nodelets :
                      (1 + m_num_rows/m_num_nodelets)),
                  m_row_blocks(NULL),
                  m_row_blocks_repl(NULL)
            {
#ifdef DEBUG                
                  std::cout << "Debug vector : m_num_nodelets = " << m_num_nodelets
                          << ", m_num_rows = " << m_num_rows
                          << ", m_num_rows_per_nodelet = " << m_num_rows_per_nodelet
                          << std::endl;
#endif
                // Allocated distributed (pointers to) blocks of rows
                m_row_blocks = (pSparseRow **)
                    mw_malloc2d(m_num_nodelets, m_num_rows_per_nodelet * sizeof(pSparseRow));
                mw_replicated_init((long *)&m_row_blocks_repl, (long)m_row_blocks);

                // Perform nodelet-local allocation and placement new on each row container
                for (IndexType row_index = 0; row_index < m_num_rows; ++row_index)
                {
                    size_t nodelet_id(nodeID(row_index));
                    size_t row_id(nodeRowID(row_index));
                    //std::cerr << "DEBUG: allocating row " << row_index << " on nodelet "
                             // << nodelet_id << " at index " << row_id << std::endl;
                    pSparseRow *lvar = m_row_blocks_repl[nodelet_id];

                    m_row_blocks_repl[nodelet_id][row_id] =
                        (pSparseRow)mw_localmalloc(sizeof(pSparseRow),
                                                   m_row_blocks_repl[nodelet_id]);
                    pSparseRow dummyPtr = new(lvar[row_id]) SparseRow();
                    //std::cout << dummyPtr << std::endl ;
                    dummyPtr = dummyPtr;
                }
#ifdef DEBUG  
                std::cout << "LilSparseMatrix ctor: " << this << std::endl<< std::endl;
		
                printInfo(std::cout, "FirstTimePRint of Object ");
#endif
            }

            // Destructor
            ~LilSparseMatrix()
            {
#ifdef DEBUG                
                std::cout << "LilSparseMatrix dtor: " << this << std::endl;
#endif
                // Clean up nodelet data
                for (IndexType row_index = 0; row_index < m_num_rows; ++row_index)
                {
                    m_row_blocks[nodeID(row_index)][nodeRowID(row_index)]->~SparseRow();
                    m_row_blocks[nodeID(row_index)][nodeRowID(row_index)] = NULL;
                }
                mw_free(m_row_blocks);
                m_row_blocks = NULL;
            }

                     template<typename RAIteratorI,
                     typename RAIteratorJ,
                     typename RAIteratorV,
                     typename DupT>
            Info build(RAIteratorI  i_it,
                       RAIteratorJ  j_it,
                       RAIteratorV  v_it,
                       IndexType    n,
                       DupT         dup)
            {
                /// @todo should this function throw an error if matrix is not empty

                /// @todo should this function call clear?
                //clear();

                /// @todo DOING SOMETHING REALLY STUPID RIGHT NOW
#ifdef DEBUG
              std::cout<<"Debug : 1 Build method from LilSparse Started"<<std::endl;
#endif
              
                for (IndexType ix = 0; ix < n; ++ix)
                {
                    setElement(*i_it, *j_it, *v_it, dup);
                    ++i_it; ++j_it; ++v_it;
                }
#ifdef DEBUG  
                printInfo(std::cout, "after build");
#endif
                return SUCCESS;
            }


            void clear()
            {
                /// @todo make atomic? transactional?
                m_nvals = 0;
                for (IndexType row = 0; row < m_num_rows; ++row)
                {
                    //m_data[row].clear();
                    rowData(row).clear();
                }
            }

            IndexType nrows() const { return m_num_rows; }
            IndexType ncols() const { return m_num_cols; }
            IndexType nvals() const { return m_nvals; }

            /// Version 1 of getshape that assigns to two passed parameters
            // void get_shape(IndexType &num_rows, IndexType &num_cols) const
            // {
            //     num_rows = m_num_rows;
            //     num_cols = m_num_cols;
            // }

            bool hasElement(IndexType irow, IndexType icol) const
            {
                if (irow >= m_num_rows || icol >= m_num_cols)
                {
                    std::cerr<<"throw IndexOutOfBoundsException(\"get_value_at: index out of bounds\")\n";
                }
                // if (m_data.empty())
                if (m_row_blocks_repl == NULL)
                {
                    return false;
                }

                //if (m_data.at(irow).empty())
                if (rowData(irow).empty())
                {
                    return false;
                }

                ScalarT val;
                //for (auto tupl : m_data[irow])// Range-based loop, access by value
                //for (auto tupl : m_data.at(irow))// Range-based loop, access by value
                for (auto& tupl : rowData(irow))
                {
                    if (std::get<0>(tupl) == icol)
                    {
                        return true;
                    }
                }
                return false;
            }

            // Get value at index
            ScalarT extractElement(IndexType irow, IndexType icol) const
            {
                if (irow >= m_num_rows || icol >= m_num_cols)
                {
                    std::cerr<<"throw IndexOutOfBoundsException('get_value_at: index out of bounds')\n";
                }
                //if (m_data.empty())
                if (m_row_blocks_repl == NULL)
                {
                    std::cerr<<"throw NoValueException('get_value_at: no rows allocated')\n";
                }

                //if (m_data.at(irow).empty())
                if (rowData(irow).empty())
                {
                    std::cerr<<"throw NoValueException('get_value_at: no entry at index')";
                }

                ScalarT val;
                //for (auto tupl : m_data[irow])// Range-based loop, access by value
                //for (auto tupl : m_data.at(irow))// Range-based loop, access by value
                for (auto &tupl : rowData(irow))
                {
                    if (std::get<0>(tupl) == icol)
                    {
                        return std::get<1>(tupl);
                    }
                }
                std::cerr<<"throw NoValueException('get_value_at: no entry at index')";
            }

            // Set value at index
            void setElement(IndexType irow, IndexType icol, ScalarT const &val)
            {
                if (irow >= m_num_rows || icol >= m_num_cols)
                {
                    std::cerr<<"throw IndexOutOfBoundsException(\"setElement: index out of bounds\")";
                }

                auto& row = rowData(irow);
                //m_data[irow].reserve(m_data[irow].capacity() + 10);

                if (row.empty()) //m_data[irow].empty())
                {
                    row.push_back(std::make_tuple(icol, val));
                    ++m_nvals;
                }
                if (std::get<0>(row.begin()) > icol)
                {
                    row.insert(row.begin(), std::make_tuple(icol, val));
                    ++m_nvals;
                }
                else
                {
                    typename std::vector<std::tuple<IndexType, ScalarT>>::iterator it;
                    for (it = row.begin(); it != row.end(); ++it)
                    {
                        if (std::get<0>(*it) == icol)
                        {
                            it = row.erase(it);
                            row.insert(it, std::make_tuple(icol, val));
                            ++m_nvals;
                            return;
                        }
                        else if (std::get<0>(*it) > icol)
                        {
                            row.insert(it, std::make_tuple(icol, val));
                            ++m_nvals;
                            return;
                        }
                    }
                    row.push_back(std::make_tuple(icol, val));
                    ++m_nvals;
                }
            }

            // Set value at index + 'merge' with any existing value
            // according to the BinaryOp passed.
            template <typename BinaryOpT>
            void setElement(IndexType irow, IndexType icol, ScalarT const &val,
                            BinaryOpT merge)
            {

                if (irow >= m_num_rows || icol >= m_num_cols)
                {
                    std::cerr<<"throw IndexOutOfBoundsException(\"setElement(merge): index out of bounds\")";
                }
#ifdef DEBUG  
                std::cout << "setElement, irow " << irow
                          << '\t' << "icol " << icol
                          << '\t' << "val " << val
                          << '\t' << "Nodelet num = "<< nodeID(irow)
                          << '\t' << "nodelet row = " << nodeRowID(irow) << std::endl;
#endif
                auto &row(rowData(irow));
                if (row.empty())
                {
                    row.push_back(std::make_tuple(icol, val));
                    ++m_nvals;
                }
                else
                {
                    typename std::vector<std::tuple<IndexType, ScalarT>>::iterator it;
                    for (it = row.begin(); it != row.end(); it++)
                    {
                        if (std::get<0>(*it) == icol)
                        {
                            // merge with existing stored value
                            std::get<1>(*it) = merge(std::get<1>(*it), val);
                            //it = m_data[irow].erase(it);
                            //m_data[irow].insert(it, std::make_tuple(icol, tmp));
                            return;
                        }
                        else if (std::get<0>(*it) > icol)
                        {
                            row.insert(it, std::make_tuple(icol, val));
                            ++m_nvals;
                            return;
                        }
                    }
                    row.push_back(std::make_tuple(icol, val));
                    ++m_nvals;
                }
            }

            typedef std::vector<std::tuple<IndexType, ScalarT>> const & RowType;
            RowType getRow(IndexType row_index) const
            {
                return rowData(row_index);
            }

            // Allow casting
            template <typename OtherScalarT>
            void setRow(
                IndexType row_index,
                std::vector<std::tuple<IndexType, OtherScalarT> > const &new_row_data)
            {
                auto &row(rowData(row_index));
                IndexType old_nvals = row.size();
                IndexType new_nvals = new_row_data.size();

                m_nvals = m_nvals + new_nvals - old_nvals;
                //m_data[row_index] = new_row_data;   // swap here?
                row.clear();
                for (auto &tupl : new_row_data)
                {
                    row.push_back(
                        std::make_tuple(std::get<0>(tupl),
                                        static_cast<ScalarT>(std::get<1>(tupl))));
                }
            }

            // When not casting vector assignment used
            void setRow(
                IndexType row_index,
                std::vector<std::tuple<IndexType, ScalarT> > const &new_row_data)
            {
                auto &row(rowData(row_index));
                IndexType old_nvals = row.size();
                IndexType new_nvals = new_row_data.size();

                m_nvals = m_nvals + new_nvals - old_nvals;
                row = new_row_data;   // swap here?
            }

            /// @todo need move semantics.
            typedef std::vector<std::tuple<IndexType, ScalarT> > const ColType;
            ColType getCol(IndexType col_index) const
            {
                std::vector<std::tuple<IndexType, ScalarT> > data;

                for (IndexType ii = 0; ii < m_num_rows; ii++)
                {
                    auto &row(rowData(ii));
                    if (!row.empty())
                    {
                        for (auto tupl : row)
                        {
                            if (std::get<0>(tupl) == col_index)
                            {
                                data.push_back(std::make_tuple(ii, std::get<1>(tupl)));
                            }
                        }
                    }
                }

                return data;
            }

            // col_data must be in increasing index order
            /// @todo this could be vastly improved.
            template <typename OtherScalarT>
            void setCol(
                IndexType col_index,
                std::vector<std::tuple<IndexType, OtherScalarT> > const &col_data)
            {
                auto it = col_data.begin();
                for (IndexType row_index = 0; row_index < m_num_rows; row_index++)
                {
                    auto &row(rowData(row_index));

                    // Check for any values to clear: either there are column entries
                    // left to examine, or the index is less than the next one to
                    // insert

                    // No value to insert in this row.
                    if ((it == col_data.end()) || (row_index < std::get<0>(*it)))
                    {
                        for (auto row_it = row.begin();
                             row_it != row.end();
                             ++row_it)
                        {
                            if (std::get<0>(*row_it) == col_index)
                            {
                                //std::cerr << "Erasing row element" << std::endl;
                                row.erase(row_it);
                                --m_nvals;
                                break;
                            }
                        }
                    }
                    // replace existing or insert
                    else if (row_index == std::get<0>(*it))
                    {
                        //std::cerr << "Row index matches col_data row" << std::endl;
                        bool inserted=false;
                        for (auto row_it = row.begin();
                             row_it != row.end();
                             ++row_it)
                        {
                            if (std::get<0>(*row_it) == col_index)
                            {
                                //std::cerr << "Found row element to replace" << std::endl;
                                // replace
                                std::get<1>(*row_it) =
                                    static_cast<ScalarT>(std::get<1>(*it));
                                ++it;
                                inserted = true;
                                break;
                            }
                            else if (std::get<0>(*row_it) > col_index)
                            {
                                //std::cerr << "Inserting new row element" << std::endl;
                                row.insert(
                                    row_it,
                                    std::make_tuple(
                                        col_index,
                                        static_cast<ScalarT>(std::get<1>(*it))));
                                ++m_nvals;
                                ++it;
                                inserted = true;
                                break;
                            }
                        }
                        if (!inserted)
                        {
                            //std::cerr << "Appending new row element" << std::endl;
                            row.insert(
                                row.end(),
                                std::make_tuple(
                                    col_index,
                                    static_cast<ScalarT>(std::get<1>(*it))));
                            ++m_nvals;
                            ++it;
                        }
                    }
                    else // row_index > next entry to insert
                    {
                        // This should not happen
                        std::cerr<<"throw GraphBLAS::PanicException(\"LilSparseMatrix::setCol() INTERNAL ERROR\")";
                    }
                }

            }

            // Get column indices for a given row
            void getColumnIndices(IndexType irow, IndexArrayType &v) const
            {
                if (irow >= m_num_rows)
                {
                    std::cerr<<"throw IndexOutOfBoundsException(\"getColumnIndices: index out of bounds\")";
                }

                auto &row(rowData(irow));
                if (!row.empty())
                {
                    IndexType ind;
                    ScalarT val;
                    v.resize(0);

                    for (auto &tupl : row)
                    {
                        std::tie(ind, val) = tupl;
                        v.push_back(ind);
                    }
                }
            }

            // Get row indices for a given column
            void getRowIndices(IndexType icol, IndexArrayType &v) const
            {
                if (icol >= m_num_cols)
                {
                    std::cerr<<"throw IndexOutOfBoundsException(\"getRowIndices: index out of bounds\")";
                }

                IndexType ind;
                ScalarT val;
                v.resize(0);

                for (IndexType ii = 0; ii < m_num_rows; ii++)
                {
                    auto &row(rowData(ii));
                    if (!row.empty())
                    {
                        for (auto tupl : row)
                        {
                            std::tie(ind, val) = tupl;
                            if (ind == icol)
                            {
                                v.push_back(ii);
                                break;
                            }
                            if (ind > icol)
                            {
                                break;
                            }
                        }
                    }
                }
            }

            template<typename RAIteratorIT,
                     typename RAIteratorJT,
                     typename RAIteratorVT>
            ScalarT extractTuples(RAIteratorIT        row_it,
                                  RAIteratorJT        col_it,
                                  RAIteratorVT        values) const
            {
                for (IndexType irow = 0; irow < m_num_rows; ++irow)
                {
                    auto &row(rowData(irow));
                    for (auto it = row.begin(); it != row.end(); ++it)
                    {
                        *row_it = row;              ++row_it;
                        *col_it = std::get<0>(*it); ++col_it;
                        *values = std::get<1>(*it); ++values;
                    }
                }
            }

            void printInfo(std::ostream &ostr, std::string const &name = "(noname)") const
            {
                ostr << name << ": size = " << m_num_rows << "x" << m_num_cols
                     << ", nvals = " << m_nvals << std::endl;
                ostr << "m_row_blocks addr: " << m_row_blocks << std::endl;
                ostr << "m_row_blocks_repl addr: " << m_row_blocks << std::endl;

                for (int i = 0; i<m_num_rows; i++)
                {
                    size_t node_id(nodeID(i));
                    size_t row_id(nodeRowID(i));

                    ostr << "Nodelet[" << node_id << ']' << "[" << row_id << "], addr = "
                         << &rowData(i) << ": ";
                    for (auto it = rowData(i).begin(); it != rowData(i).end(); ++it)
                    {
                        ostr << "\t(" << std::get<0>(*it) << " : " << std::get<1>(*it) << ")";
                    }
                    ostr << std::endl;
                }
            }

        private:
            IndexType m_num_rows;
            IndexType m_num_cols;
            IndexType m_nvals;

            // struct nMapper
            // {
            //     int i;
            //     int j;
            // };
            // nMapper x;

            // void nodeletRowMapper(IndexType rowNumber, size_t &node_num, size_t &node_row_id)
            // {
            //     if (rowNumber < m_num_nodelets)
            //     {
            //         node_num = rowNumber;
            //         node_row_id = 1;
            //     }
            //     else
            //     {
            //         node_num = rowNumber % m_num_nodelets;
            //         node_row_id = rowNumber / m_num_nodelets;
            //     }
            // }

            size_t const m_num_nodelets;
            size_t const m_num_rows_per_nodelet;

            size_t nodeID(IndexType row_index) const
            {
                return row_index % m_num_nodelets;
            }

            size_t nodeRowID(IndexType row_index) const
            {
                return row_index / m_num_nodelets;
            }

            typedef std::vector<std::tuple<IndexType, ScalarT>>* pSparseRow;
            typedef std::vector<std::tuple<IndexType, ScalarT>>   SparseRow;

            SparseRow const &rowData(IndexType row_index) const
            {
                return *m_row_blocks_repl[nodeID(row_index)][nodeRowID(row_index)];
            }
            SparseRow &rowData(IndexType row_index)
            {
                return *m_row_blocks_repl[nodeID(row_index)][nodeRowID(row_index)];
            }

            pSparseRow **m_row_blocks;
            replicated pSparseRow **m_row_blocks_repl;

            // List-of-lists storage (LIL)
            //std::vector<std::vector<std::tuple<IndexType, ScalarT>>> m_data;
        };
    } // namespace backend
} // namespace GraphBLAS

#endif // GB_SEQUENTIAL_LILSPARSEMATRIX_HPP
