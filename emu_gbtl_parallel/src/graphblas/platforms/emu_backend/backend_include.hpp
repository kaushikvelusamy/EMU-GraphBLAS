#if(GB_INCLUDE_BACKEND_ALL)
#include <graphblas/platforms/emu_backend/emu_backend.hpp>
#endif

#if(GB_INCLUDE_BACKEND_MATRIX)
#include <graphblas/platforms/emu_backend/Matrix.hpp>
#undef GB_INCLUDE_BACKEND_MATRIX
#endif

#if(GB_INCLUDE_BACKEND_OPERATIONS)
#include <graphblas/platforms/emu_backend/operations.hpp>
#undef GB_INCLUDE_BACKEND_OPERATIONS
#endif


#if(GB_INCLUDE_BACKEND_TRANSPOSE_VIEW)
#include <graphblas/platforms/emu_backend/TransposeView.hpp>
#undef GB_INCLUDE_BACKEND_TRANSPOSE_VIEW
#endif

