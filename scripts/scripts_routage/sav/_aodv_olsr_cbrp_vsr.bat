


echo "VSR 12 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\mobility\xxx\vsr_12\
move results\*.* a\mobility\xxx\vsr_12\cdcl\



op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 2		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 4		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 6		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 8		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 10		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 12		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 14		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\nb_connections\xxx\vsr_12\
move results\*.* a\nb_connections\xxx\vsr_12\cdcl\



op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\nb_nodes\xxx\vsr_12\
move results\*.* a\nb_nodes\xxx\vsr_12\cdcl



op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 2100 -Y_MAX 2100	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1900 -Y_MAX 1900	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1700 -Y_MAX 1700	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1500 -Y_MAX 1500	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1200 -Y_MAX 1200	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 800  -Y_MAX 800 	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\degree\xxx\vsr_12\
move results\*.* a\degree\xxx\vsr_12\cdcl



op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 5		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 10		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 15		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 20		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 25		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 30		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\repair_mobility\xxx\vsr_12\
move results\*.* a\repair_mobility\xxx\vsr_12\cdcl\








echo "VSR 23 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\mobility\xxx\vsr_23\
move results\*.* a\mobility\xxx\vsr_23\cdcl\



op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 2		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 4		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 6		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 8		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 10		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 12		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 14		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\nb_connections\xxx\vsr_23\
move results\*.* a\nb_connections\xxx\vsr_23\cdcl\



op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\nb_nodes\xxx\vsr_23\
move results\*.* a\nb_nodes\xxx\vsr_23\cdcl



op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 2100 -Y_MAX 2100	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1900 -Y_MAX 1900	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1700 -Y_MAX 1700	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1500 -Y_MAX 1500	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1200 -Y_MAX 1200	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 800  -Y_MAX 800 	-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\degree\xxx\vsr_23\
move results\*.* a\degree\xxx\vsr_23\cdcl



op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 5		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 10		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 15		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 20		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 25		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_repair_mobility -SP_LOW_MAX 30		-seed xxx 	-SP_LOW_MOBILITY_MODEL 1  	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\repair_mobility\xxx\vsr_23\
move results\*.* a\repair_mobility\xxx\vsr_23\cdcl\
















echo "OLSR Seed xxx"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed xxx 
move results_olsr\*.* a\mobility\xxx\olsr\


op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 14	-seed xxx 
move results_olsr\*.* a\nb_connections\xxx\olsr\



op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 
move results_olsr\*.* a\nb_nodes\xxx\olsr\



op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 2100 -Y_MAX 2100	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1900 -Y_MAX 1900	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1700 -Y_MAX 1700	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1500 -Y_MAX 1500	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1200 -Y_MAX 1200	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 800  -Y_MAX 800 	-seed xxx 
move results_olsr\*.* a\degree\xxx\olsr\







echo "AODV Seed xxx"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed xxx 
move results_aodv\*.* a\mobility\xxx\aodv\


op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 14	-seed xxx 
move results_aodv\*.* a\nb_connections\xxx\aodv\



op_runsim -net_name _aodv-20 -noprompt 	-ef aodv_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 
op_runsim -net_name _aodv-30 -noprompt 	-ef aodv_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 
op_runsim -net_name _aodv-50 -noprompt 	-ef aodv_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 
op_runsim -net_name _aodv-70 -noprompt 	-ef aodv_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 
op_runsim -net_name _aodv-80 -noprompt 	-ef aodv_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 
move results_aodv\*.* a\nb_nodes\xxx\aodv\



op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 2100 -Y_MAX 2100	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1900 -Y_MAX 1900	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1700 -Y_MAX 1700	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1500 -Y_MAX 1500	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1200 -Y_MAX 1200	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 800  -Y_MAX 800	-seed xxx 
move results_aodv\*.* a\degree\xxx\aodv\







echo "CBRP Seed xxx"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed xxx 
move results_cbrp\*.* a\mobility\xxx\cbrp\


op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 14	-seed xxx 
move results_cbrp\*.* a\nb_connections\xxx\cbrp\



op_runsim -net_name _cbrp-20 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 
op_runsim -net_name _cbrp-30 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 
op_runsim -net_name _cbrp-50 -noprompt 	-ef cbrp_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 
op_runsim -net_name _cbrp-70 -noprompt 	-ef cbrp_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 
op_runsim -net_name _cbrp-80 -noprompt 	-ef cbrp_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 
move results_cbrp\*.* a\nb_nodes\xxx\cbrp\



op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 2100 -Y_MAX 2100	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1900 -Y_MAX 1900	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1700 -Y_MAX 1700	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1500 -Y_MAX 1500	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1200 -Y_MAX 1200	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 800  -Y_MAX 800	-seed xxx 
move results_cbrp\*.* a\degree\xxx\cbrp\



op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_repair_mobility -SP_LOW_MAX 30			-seed xxx 
move results_cbrp\*.* a\repair_mobility\xxx\cbrp\







