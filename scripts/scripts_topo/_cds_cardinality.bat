

rem "NB NODES"


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-10 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 400  -Y_MAX 400	 	-seed xxx
op_runsim -net_name _cdcl-20 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1100 -Y_MAX 1100 	-seed xxx
op_runsim -net_name _cdcl-30 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1700 -Y_MAX 1700 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2100 -Y_MAX 2100 	-seed xxx
op_runsim -net_name _cdcl-50 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2350 -Y_MAX 2350 	-seed xxx
op_runsim -net_name _cdcl-60 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2570 -Y_MAX 2570 	-seed xxx
op_runsim -net_name _cdcl-70 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2800 -Y_MAX 2800 	-seed xxx
op_runsim -net_name _cdcl-100 -noprompt -ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 3320 -Y_MAX 3320 	-seed xxx
move results\*.* a\nb_nodes\xxx\cds_1
