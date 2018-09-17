************************************************
Program Name/Arguments: 
./gbtl_tc.mwx 
demo/dataset/tc-small-data.tsv 
************************************************
Simulator Version: EMUSIM-18.08
************************************************
Configuration Details:
Gossamer Cores per Nodelet=1
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=true
Timing sample interval (ns)=10000
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=175 MHz, Pd=5.714
Memory DDR4-1600: Bandwidth = 1.416 GiB/s = 1.521 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
PROGRAM ENDED.
Emu system run time 0.407 sec==407011648400 ps
System thread counts:
	active=0, created=1, died=1,
	max live=1 first occurred @0 s with prog 0% complete
	and last occurred @0 s with prog 0% complete
Num_Core_Cycles=71230600
Num_SRIO_Cycles=254382280
Num_Mem_Cycles=77378640
************************************************
MEMORY MAP
545364,722,862,795,1,1,1,1
721,10787,1,0,0,0,0,0
862,0,13928,1,0,0,0,0
796,0,0,12418,0,0,0,0
1,0,0,0,4,0,0,0
1,0,0,0,0,4,0,0
1,0,0,0,0,0,4,0
1,0,0,0,0,0,0,4

************************************************
REMOTES MAP
0,117,162,139,9,9,9,9
35,0,0,0,0,0,0,0
48,0,0,0,0,0,0,0
42,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 0, 1, 2383, 125, 454, 0.00824766, 0.0433049
NLET[1]: 0, 0, 0, 722, 117, 35, 0.000180928, 0.000951403
NLET[2]: 0, 0, 0, 863, 162, 48, 0.000231563, 0.00121313
NLET[3]: 0, 0, 0, 796, 139, 42, 0.000207228, 0.00108886
NLET[4]: 0, 0, 0, 1, 9, 0, 2.06775e-07, 4.77323e-07
NLET[5]: 0, 0, 0, 1, 9, 0, 2.06775e-07, 4.77323e-07
NLET[6]: 0, 0, 0, 1, 9, 0, 2.06775e-07, 4.77323e-07
NLET[7]: 0, 0, 0, 1, 9, 0, 2.06775e-07, 4.77323e-07

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 2962, 0.000790334, 2962, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 874, 0.000236247, 874, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 1073, 0.000282954, 1073, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 977, 0.000260745, 977, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 10, 4.49245e-07, 10, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 10, 4.49245e-07, 10, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 10, 4.49245e-07, 10, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 10, 4.49245e-07, 10, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 2962, 0.000781097, 4.16158e-05, 1, 0, -nan, 4.16158e-05, 1
ME[0].ToNQM[1]: 874, 0.000238549, 1.22729e-05, 1, 0, -nan, 1.22729e-05, 1
ME[0].ToNQM[2]: 1073, 0.000286155, 1.50681e-05, 1, 0, -nan, 1.50681e-05, 1
ME[0].ToNQM[3]: 977, 0.000263468, 1.37196e-05, 1, 0, -nan, 1.37196e-05, 1
ME[0].ToNQM[4]: 10, 7.01946e-07, 1.40389e-07, 1, 0, -nan, 1.40389e-07, 1
ME[0].ToNQM[5]: 10, 7.01946e-07, 1.40389e-07, 1, 0, -nan, 1.40389e-07, 1
ME[0].ToNQM[6]: 10, 7.01946e-07, 1.40389e-07, 1, 0, -nan, 1.40389e-07, 1
ME[0].ToNQM[7]: 10, 7.01946e-07, 1.40389e-07, 1, 0, -nan, 1.40389e-07, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 512
