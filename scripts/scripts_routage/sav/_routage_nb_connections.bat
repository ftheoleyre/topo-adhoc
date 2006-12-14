


echo "VSR 12 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 15		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 20		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 30		-seed xxx 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 40		-seed xxx 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\nb_connections\xxx\vsr_12\


echo "VSR 23 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 15		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 20		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 30		-seed xxx 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_nb_connections -NB_CONNECTIONS 40		-seed xxx 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\nb_connections\xxx\vsr_23\


echo "OLSR Seed xxx"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 15	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 20	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 30	-seed xxx 
op_runsim -net_name _olsr-40 -noprompt -ef olsr_nb_connections -NB_CONNECTIONS 40	-seed xxx 
move results_olsr\*.* a\nb_connections\xxx\olsr\



echo "AODV Seed xxx"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 15	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 20	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 30	-seed xxx 
op_runsim -net_name _aodv-40 -noprompt -ef aodv_nb_connections -NB_CONNECTIONS 40	-seed xxx 
move results_aodv\*.* a\nb_connections\xxx\aodv\



echo "CBRP Seed xxx"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 15	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 20	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 30	-seed xxx 
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_nb_connections -NB_CONNECTIONS 40	-seed xxx 
move results_cbrp\*.* a\nb_connections\xxx\cbrp\








