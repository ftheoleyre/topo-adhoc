


echo "VSR 12 Seed xxx"

op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5			-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10			-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15			-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20			-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25			-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30			-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\mobility\xxx\vsr_12\
move results\*.* a\mobility\xxx\vsr_12\cdcl\



op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 2		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 4		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 6		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 8		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 10		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 12		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 14		-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\nb_connections\xxx\vsr_12\
move results\*.* a\nb_connections\xxx\vsr_12\cdcl\



op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_nb_nodes -X_MAX 790  -Y_MAX 2529	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_nb_nodes -X_MAX 968  -Y_MAX 3098	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1118 -Y_MAX 3577	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_nb_nodes -X_MAX 1250 -Y_MAX 4000	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1369 -Y_MAX 4381	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_nb_nodes -X_MAX 1479 -Y_MAX 4732	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_nb_nodes -X_MAX 1581 -Y_MAX 5059	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-90 -noprompt 	-ef vsr_nb_nodes -X_MAX 1677 -Y_MAX 5366	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-100 -noprompt 	-ef vsr_nb_nodes -X_MAX 1767 -Y_MAX 5656	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-120 -noprompt 	-ef vsr_nb_nodes -X_MAX 1936 -Y_MAX 6196	-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\nb_nodes\xxx\vsr_12\
move results\*.* a\nb_nodes\xxx\vsr_12\cdcl


op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1200 -Y_MAX 3840	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1000 -Y_MAX 3200	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 900  -Y_MAX 2880	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 800  -Y_MAX 2560	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 600  -Y_MAX 1920	-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 500  -Y_MAX 1600 	-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\density\xxx\vsr_12\
move results\*.* a\density\xxx\vsr_12\cdcl



op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30		-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\repair_mobility\xxx\vsr_12\
move results\*.* a\repair_mobility\xxx\vsr_12\cdcl\








echo "VSR 23 Seed xxx"

op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5			-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10			-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15			-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20			-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25			-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30			-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\mobility\xxx\vsr_23\
move results\*.* a\mobility\xxx\vsr_23\cdcl\



op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 2		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 4		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 6		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 8		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 10		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 12		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 14		-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\nb_connections\xxx\vsr_23\
move results\*.* a\nb_connections\xxx\vsr_23\cdcl\



op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_nb_nodes -X_MAX 790  -Y_MAX 2529	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_nb_nodes -X_MAX 968  -Y_MAX 3098	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_nb_nodes -X_MAX 1118 -Y_MAX 3577	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_nb_nodes -X_MAX 1250 -Y_MAX 4000	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1369 -Y_MAX 4381	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_nb_nodes -X_MAX 1479 -Y_MAX 4732	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_nb_nodes -X_MAX 1581 -Y_MAX 5059	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-90 -noprompt 	-ef vsr_nb_nodes -X_MAX 1677 -Y_MAX 5366	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-100 -noprompt 	-ef vsr_nb_nodes -X_MAX 1767 -Y_MAX 5656	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-120 -noprompt 	-ef vsr_nb_nodes -X_MAX 1936 -Y_MAX 6196	-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\nb_nodes\xxx\vsr_23\
move results\*.* a\nb_nodes\xxx\vsr_23\cdcl




op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1200 -Y_MAX 3840	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 1000 -Y_MAX 3200	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 900  -Y_MAX 2880	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 800  -Y_MAX 2560	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 600  -Y_MAX 1920	-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_nb_nodes -X_MAX 500  -Y_MAX 1600 	-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\density\xxx\vsr_23\
move results\*.* a\density\xxx\vsr_23\cdcl



op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-60 -noprompt -ef vsr_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30		-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\repair_mobility\xxx\vsr_23\
move results\*.* a\repair_mobility\xxx\vsr_23\cdcl\








echo "OLSR Seed xxx"

op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30			-seed xxx 
move results_olsr\*.* a\mobility\xxx\olsr\


op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _olsr-60 -noprompt -ef olsr_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 14	-seed xxx 
move results_olsr\*.* a\nb_connections\xxx\olsr\


op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_nb_nodes -X_MAX 790  -Y_MAX 2529	-seed xxx
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_nb_nodes -X_MAX 968  -Y_MAX 3098	-seed xxx
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_nb_nodes -X_MAX 1118 -Y_MAX 3577	-seed xxx
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_nb_nodes -X_MAX 1250 -Y_MAX 4000	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 1369 -Y_MAX 4381	-seed xxx
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_nb_nodes -X_MAX 1479 -Y_MAX 4732	-seed xxx
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_nb_nodes -X_MAX 1581 -Y_MAX 5059	-seed xxx
op_runsim -net_name _olsr-90 -noprompt 	-ef olsr_nb_nodes -X_MAX 1677 -Y_MAX 5366	-seed xxx
op_runsim -net_name _olsr-100 -noprompt -ef olsr_nb_nodes -X_MAX 1767 -Y_MAX 5656	-seed xxx
op_runsim -net_name _olsr-120 -noprompt -ef olsr_nb_nodes -X_MAX 1936 -Y_MAX 6196	-seed xxx
move results_olsr\*.* a\nb_nodes\xxx\olsr\



op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 1200 -Y_MAX 3840	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 1000 -Y_MAX 3200	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 900  -Y_MAX 2880	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 800  -Y_MAX 2560	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 600  -Y_MAX 1920	-seed xxx
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_nb_nodes -X_MAX 500  -Y_MAX 1600 	-seed xxx
move results_olsr\*.* a\density\xxx\olsr\







echo "AODV Seed xxx"

op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_mobility -X_MAX 1500 -Y_MAX 4800s -SP_LOW_MAX 30			-seed xxx 
move results_aodv\*.* a\mobility\xxx\aodv\


op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _aodv-60 -noprompt -ef aodv_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 14	-seed xxx 
move results_aodv\*.* a\nb_connections\xxx\aodv\



op_runsim -net_name _aodv-20 -noprompt 	-ef aodv_nb_nodes -X_MAX 790  -Y_MAX 2529	-seed xxx
op_runsim -net_name _aodv-30 -noprompt 	-ef aodv_nb_nodes -X_MAX 968  -Y_MAX 3098	-seed xxx
op_runsim -net_name _aodv-40 -noprompt 	-ef aodv_nb_nodes -X_MAX 1118 -Y_MAX 3577	-seed xxx
op_runsim -net_name _aodv-50 -noprompt 	-ef aodv_nb_nodes -X_MAX 1250 -Y_MAX 4000	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 1369 -Y_MAX 4381	-seed xxx
op_runsim -net_name _aodv-70 -noprompt 	-ef aodv_nb_nodes -X_MAX 1479 -Y_MAX 4732	-seed xxx
op_runsim -net_name _aodv-80 -noprompt 	-ef aodv_nb_nodes -X_MAX 1581 -Y_MAX 5059	-seed xxx
op_runsim -net_name _aodv-90 -noprompt 	-ef aodv_nb_nodes -X_MAX 1677 -Y_MAX 5366	-seed xxx
op_runsim -net_name _aodv-100 -noprompt -ef aodv_nb_nodes -X_MAX 1767 -Y_MAX 5656	-seed xxx
op_runsim -net_name _aodv-120 -noprompt -ef aodv_nb_nodes -X_MAX 1936 -Y_MAX 6196	-seed xxx
move results_aodv\*.* a\nb_nodes\xxx\aodv\



op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 1200 -Y_MAX 3840	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 1000 -Y_MAX 3200	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 900  -Y_MAX 2880	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 800  -Y_MAX 2560	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 600  -Y_MAX 1920	-seed xxx
op_runsim -net_name _aodv-60 -noprompt 	-ef aodv_nb_nodes -X_MAX 500  -Y_MAX 1600 	-seed xxx
move results_aodv\*.* a\density\xxx\aodv\







echo "CBRP Seed xxx"

op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5			-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10			-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15			-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20			-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25			-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30			-seed xxx 
move results_cbrp\*.* a\mobility\xxx\cbrp\


op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 2	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 4	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 6	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 8	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 10	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 12	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_nb_connections -X_MAX 1500 -Y_MAX 4800 -NB_CONNECTIONS 14	-seed xxx 
move results_cbrp\*.* a\nb_connections\xxx\cbrp\



op_runsim -net_name _cbrp-20 -noprompt 	-ef cbrp_nb_nodes -X_MAX 790  -Y_MAX 2529	-seed xxx
op_runsim -net_name _cbrp-30 -noprompt 	-ef cbrp_nb_nodes -X_MAX 968  -Y_MAX 3098	-seed xxx
op_runsim -net_name _cbrp-40 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1118 -Y_MAX 3577	-seed xxx
op_runsim -net_name _cbrp-50 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1250 -Y_MAX 4000	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1369 -Y_MAX 4381	-seed xxx
op_runsim -net_name _cbrp-70 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1479 -Y_MAX 4732	-seed xxx
op_runsim -net_name _cbrp-80 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1581 -Y_MAX 5059	-seed xxx
op_runsim -net_name _cbrp-90 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1677 -Y_MAX 5366	-seed xxx
op_runsim -net_name _cbrp-100 -noprompt -ef cbrp_nb_nodes -X_MAX 1767 -Y_MAX 5656	-seed xxx
op_runsim -net_name _cbrp-120 -noprompt -ef cbrp_nb_nodes -X_MAX 1936 -Y_MAX 6196	-seed xxx
move results_cbrp\*.* a\nb_nodes\xxx\cbrp\



op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1200 -Y_MAX 3840	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 1000 -Y_MAX 3200	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 900  -Y_MAX 2880	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 800  -Y_MAX 2560	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 600  -Y_MAX 1920	-seed xxx
op_runsim -net_name _cbrp-60 -noprompt 	-ef cbrp_nb_nodes -X_MAX 500  -Y_MAX 1600 	-seed xxx
move results_cbrp\*.* a\density\xxx\cbrp\



op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 0.001	-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 5		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 10		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 15		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 20		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 25		-seed xxx 
op_runsim -net_name _cbrp-60 -noprompt -ef cbrp_repair_mobility -X_MAX 1500 -Y_MAX 4800 -SP_LOW_MAX 30		-seed xxx 
move results_cbrp\*.* a\repair_mobility\xxx\cbrp\







