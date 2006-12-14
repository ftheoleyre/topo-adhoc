rem "MOBILITE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cds_1\


echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cds_2\


echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\cdcl_23\


echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 0	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 5	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 10	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 15	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 20	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 25	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_mob -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-SP_LOW_MAX 30	-seed xxx
move results\*.* a\mob\xxx\wu_1\





rem "NB NODES"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-10 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 400  -Y_MAX 400	 	-seed xxx
op_runsim -net_name _cdcl-20 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1100 -Y_MAX 1100 	-seed xxx
op_runsim -net_name _cdcl-30 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1700 -Y_MAX 1700 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2100 -Y_MAX 2100 	-seed xxx
op_runsim -net_name _cdcl-50 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2350 -Y_MAX 2350 	-seed xxx
op_runsim -net_name _cdcl-60 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2570 -Y_MAX 2570 	-seed xxx
op_runsim -net_name _cdcl-70 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2800 -Y_MAX 2800 	-seed xxx
op_runsim -net_name _cdcl-100 -noprompt -ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 3320 -Y_MAX 3320 	-seed xxx
move results\*.* a\nb_nodes\xxx\cds_1\

echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-10 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 400  -Y_MAX 400	 	-seed xxx
op_runsim -net_name _cdcl-20 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1100 -Y_MAX 1100 	-seed xxx
op_runsim -net_name _cdcl-30 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1700 -Y_MAX 1700 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2100 -Y_MAX 2100 	-seed xxx
op_runsim -net_name _cdcl-50 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2350 -Y_MAX 2350 	-seed xxx
op_runsim -net_name _cdcl-60 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2570 -Y_MAX 2570 	-seed xxx
op_runsim -net_name _cdcl-70 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2800 -Y_MAX 2800 	-seed xxx
op_runsim -net_name _cdcl-100 -noprompt -ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 3320 -Y_MAX 3320 	-seed xxx
move results\*.* a\nb_nodes\xxx\cds_2\

echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-10 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 400  -Y_MAX 400		-seed xxx
op_runsim -net_name _cdcl-20 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1100 -Y_MAX 1100 	-seed xxx
op_runsim -net_name _cdcl-30 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1700 -Y_MAX 1700 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2100 -Y_MAX 2100 	-seed xxx
op_runsim -net_name _cdcl-50 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2350 -Y_MAX 2350 	-seed xxx
op_runsim -net_name _cdcl-60 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2570 -Y_MAX 2570 	-seed xxx
op_runsim -net_name _cdcl-70 -noprompt 	-ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2800 -Y_MAX 2800 	-seed xxx
op_runsim -net_name _cdcl-100 -noprompt -ef cdcl_nb_nodes -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 3320 -Y_MAX 3320 	-seed xxx
move results\*.* a\nb_nodes\xxx\cdcl_23\

echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-10 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 400  -Y_MAX 400	 	-seed xxx
op_runsim -net_name _cdcl-20 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1100 -Y_MAX 1100 	-seed xxx
op_runsim -net_name _cdcl-30 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1700 -Y_MAX 1700 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2100 -Y_MAX 2100 	-seed xxx
op_runsim -net_name _cdcl-50 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2350 -Y_MAX 2350 	-seed xxx
op_runsim -net_name _cdcl-60 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2570 -Y_MAX 2570 	-seed xxx
op_runsim -net_name _cdcl-70 -noprompt 	-ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2800 -Y_MAX 2800 	-seed xxx
op_runsim -net_name _cdcl-100 -noprompt -ef cdcl_nb_nodes -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 3320 -Y_MAX 3320 	-seed xxx
move results\*.* a\nb_nodes\xxx\wu_1\





rem "DEGRE"

echo "CDS (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2500 -Y_MAX 2500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2200 -Y_MAX 2200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1800 -Y_MAX 1800 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1500 -Y_MAX 1500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1200 -Y_MAX 1200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1000 -Y_MAX 1000 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 500 -Y_MAX 500 		-seed xxx
move results\*.* a\degre\xxx\cds_1\

echo "CDS (k_cds=2)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2500 -Y_MAX 2500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 2200 -Y_MAX 2200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1800 -Y_MAX 1800 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1500 -Y_MAX 1500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1200 -Y_MAX 1200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 1000 -Y_MAX 1000 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 0	-X_MAX 500  -Y_MAX 500		-seed xxx
move results\*.* a\degre\xxx\cds_2\

echo "CDCL (k_cds=2 & k_cluster=3)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2500 -Y_MAX 2500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 2200 -Y_MAX 2200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1800 -Y_MAX 1800 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1500 -Y_MAX 1500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1200 -Y_MAX 1200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 1000 -Y_MAX 1000 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 2 -k_cluster 3 -cds_algo 3 -cluster_algo 3	-X_MAX 500  -Y_MAX 500		-seed xxx
move results\*.* a\degre\xxx\cdcl_23\

echo "WU & LI (k_cds=1)"
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2500 -Y_MAX 2500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 2200 -Y_MAX 2200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1800 -Y_MAX 1800 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1500 -Y_MAX 1500 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1200 -Y_MAX 1200 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 1000 -Y_MAX 1000 	-seed xxx
op_runsim -net_name _cdcl-40 -noprompt 	-ef cdcl_degre -k_cds 1 -k_cluster 3 -cds_algo 4 -cluster_algo 0	-X_MAX 500  -Y_MAX 500		-seed xxx
move results\*.* a\degre\xxx\wu_1\





