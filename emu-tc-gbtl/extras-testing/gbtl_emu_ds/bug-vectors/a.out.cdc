Post Untimed portion: CurrentRSS (MB)=18.875
Post Untimed portion: PeakRSS (MB)=18.875
************************************************
Program Name/Arguments: 
a.out.mwx 
************************************************
Simulator Version: EMUSIM-18.04.1
************************************************
Configuration Details:
Gossamer Cores per Nodelet=1
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=true
Timing sample interval (ns)=10000
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=150 MHz, Pd=6.667
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=18.875
Post SystemC Startup: PeakRSS (MB)=18.875
PROGRAM ENDED.
Emu system run time 0.103 sec==102573795100 ps
System thread counts:
	active=0, created=1, died=1,
	max live=1 first occurred @0 s with prog 0% complete
	and last occurred @0 s with prog 0% complete
Num_Core_Cycles=15385300
Num_SRIO_Cycles=64108621
Num_Mem_Cycles=25968049
************************************************
MEMORY MAP
116501,10,10,10,0,0,0,0
10,12,0,0,0,0,0,0
10,0,12,0,0,0,0,0
10,0,0,12,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
REMOTES MAP
0,1,1,1,1,1,1,1
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 0, 1, 30, 0, 7, 0.00582978, 0.047632
NLET[1]: 0, 0, 0, 10, 1, 0, 9.62722e-07, 5.58975e-06
NLET[2]: 0, 0, 0, 10, 1, 0, 9.62722e-07, 5.58975e-06
NLET[3]: 0, 0, 0, 10, 1, 0, 9.62722e-07, 5.58975e-06
NLET[4]: 0, 0, 0, 0, 1, 0, 3.85089e-08, 0
NLET[5]: 0, 0, 0, 0, 1, 0, 3.85089e-08, 0
NLET[6]: 0, 0, 0, 0, 1, 0, 3.85089e-08, 0
NLET[7]: 0, 0, 0, 0, 1, 0, 3.85089e-08, 0

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 37, 4.62129e-05, 37, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 11, 1.50143e-05, 11, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 11, 1.50143e-05, 11, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 11, 1.50143e-05, 11, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 1, 6.49971e-08, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 1, 6.49971e-08, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 1, 6.49971e-08, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 1, 6.49971e-08, 1, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 37, 4.5303e-05, 2.405e-06, 1, 0, -nan, 2.405e-06, 1
ME[0].ToNQM[1]: 11, 1.51443e-05, 7.14979e-07, 1, 0, -nan, 7.14979e-07, 1
ME[0].ToNQM[2]: 11, 1.51443e-05, 7.14979e-07, 1, 0, -nan, 7.14979e-07, 1
ME[0].ToNQM[3]: 11, 1.51443e-05, 7.14979e-07, 1, 0, -nan, 7.14979e-07, 1
ME[0].ToNQM[4]: 1, 1.94991e-07, 6.49971e-08, 1, 0, -nan, 6.49971e-08, 1
ME[0].ToNQM[5]: 1, 1.94991e-07, 6.49971e-08, 1, 0, -nan, 6.49971e-08, 1
ME[0].ToNQM[6]: 1, 1.94991e-07, 6.49971e-08, 1, 0, -nan, 6.49971e-08, 1
ME[0].ToNQM[7]: 1, 1.94991e-07, 6.49971e-08, 1, 0, -nan, 6.49971e-08, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=22.2852
End of simulation: PeakRSS (MB)=22.2852
************************************************
Simulator wall clock time (seconds): 134
