echo "VSR 12 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\xxx\vsr_12\


echo "VSR 23 Seed xxx"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\xxx\vsr_23\


echo "OLSR Seed xxx"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\xxx\olsr\



echo "AODV Seed xxx"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\xxx\aodv\



echo "CBRP Seed xxx"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed xxx 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\xxx\cbrp\





