rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob_boundless -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\wu_1\
