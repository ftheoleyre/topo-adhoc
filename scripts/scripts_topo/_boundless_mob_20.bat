rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 1
move results\*.* a\mob\1\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 1
move results\*.* a\mob\1\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 1
move results\*.* a\mob\1\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 1
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 1
move results\*.* a\mob\1\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 2
move results\*.* a\mob\2\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 2
move results\*.* a\mob\2\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 2
move results\*.* a\mob\2\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 2
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 2
move results\*.* a\mob\2\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 3
move results\*.* a\mob\3\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 3
move results\*.* a\mob\3\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 3
move results\*.* a\mob\3\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 3
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 3
move results\*.* a\mob\3\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 4
move results\*.* a\mob\4\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 4
move results\*.* a\mob\4\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 4
move results\*.* a\mob\4\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 4
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 4
move results\*.* a\mob\4\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 5
move results\*.* a\mob\5\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 5
move results\*.* a\mob\5\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 5
move results\*.* a\mob\5\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 5
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 5
move results\*.* a\mob\5\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 6
move results\*.* a\mob\6\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 6
move results\*.* a\mob\6\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 6
move results\*.* a\mob\6\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 6
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 6
move results\*.* a\mob\6\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 7
move results\*.* a\mob\7\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 7
move results\*.* a\mob\7\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 7
move results\*.* a\mob\7\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 7
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 7
move results\*.* a\mob\7\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 8
move results\*.* a\mob\8\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 8
move results\*.* a\mob\8\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 8
move results\*.* a\mob\8\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 8
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 8
move results\*.* a\mob\8\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 9
move results\*.* a\mob\9\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 9
move results\*.* a\mob\9\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 9
move results\*.* a\mob\9\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 9
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 9
move results\*.* a\mob\9\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 10
move results\*.* a\mob\10\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 10
move results\*.* a\mob\10\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 10
move results\*.* a\mob\10\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 10
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 10
move results\*.* a\mob\10\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 11
move results\*.* a\mob\11\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 11
move results\*.* a\mob\11\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 11
move results\*.* a\mob\11\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 11
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 11
move results\*.* a\mob\11\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 12
move results\*.* a\mob\12\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 12
move results\*.* a\mob\12\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 12
move results\*.* a\mob\12\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 12
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 12
move results\*.* a\mob\12\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 13
move results\*.* a\mob\13\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 13
move results\*.* a\mob\13\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 13
move results\*.* a\mob\13\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 13
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 13
move results\*.* a\mob\13\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 14
move results\*.* a\mob\14\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 14
move results\*.* a\mob\14\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 14
move results\*.* a\mob\14\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 14
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 14
move results\*.* a\mob\14\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 15
move results\*.* a\mob\15\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 15
move results\*.* a\mob\15\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 15
move results\*.* a\mob\15\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 15
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 15
move results\*.* a\mob\15\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 16
move results\*.* a\mob\16\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 16
move results\*.* a\mob\16\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 16
move results\*.* a\mob\16\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 16
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 16
move results\*.* a\mob\16\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 17
move results\*.* a\mob\17\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 17
move results\*.* a\mob\17\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 17
move results\*.* a\mob\17\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 17
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 17
move results\*.* a\mob\17\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 18
move results\*.* a\mob\18\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 18
move results\*.* a\mob\18\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 18
move results\*.* a\mob\18\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 18
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 18
move results\*.* a\mob\18\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 19
move results\*.* a\mob\19\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 19
move results\*.* a\mob\19\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 19
move results\*.* a\mob\19\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 19
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 19
move results\*.* a\mob\19\wu_1\
rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 20
move results\*.* a\mob\20\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed 20
move results\*.* a\mob\20\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed 20
move results\*.* a\mob\20\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed 20
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed 20
move results\*.* a\mob\20\wu_1\
