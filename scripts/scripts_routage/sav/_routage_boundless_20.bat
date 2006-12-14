echo "VSR 12 Seed 1"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\1\vsr_12\


echo "VSR 23 Seed 1"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 1 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\1\vsr_23\


echo "OLSR Seed 1"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\1\olsr\



echo "AODV Seed 1"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\1\aodv\



echo "CBRP Seed 1"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 1 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\1\cbrp\





echo "VSR 12 Seed 2"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\2\vsr_12\


echo "VSR 23 Seed 2"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 2 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\2\vsr_23\


echo "OLSR Seed 2"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\2\olsr\



echo "AODV Seed 2"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\2\aodv\



echo "CBRP Seed 2"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 2 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\2\cbrp\





echo "VSR 12 Seed 3"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\3\vsr_12\


echo "VSR 23 Seed 3"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 3 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\3\vsr_23\


echo "OLSR Seed 3"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\3\olsr\



echo "AODV Seed 3"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\3\aodv\



echo "CBRP Seed 3"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 3 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\3\cbrp\





echo "VSR 12 Seed 4"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\4\vsr_12\


echo "VSR 23 Seed 4"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 4 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\4\vsr_23\


echo "OLSR Seed 4"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\4\olsr\



echo "AODV Seed 4"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\4\aodv\



echo "CBRP Seed 4"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 4 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\4\cbrp\





echo "VSR 12 Seed 5"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\5\vsr_12\


echo "VSR 23 Seed 5"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 5 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\5\vsr_23\


echo "OLSR Seed 5"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\5\olsr\



echo "AODV Seed 5"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\5\aodv\



echo "CBRP Seed 5"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 5 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\5\cbrp\





echo "VSR 12 Seed 6"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\6\vsr_12\


echo "VSR 23 Seed 6"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 6 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\6\vsr_23\


echo "OLSR Seed 6"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\6\olsr\



echo "AODV Seed 6"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\6\aodv\



echo "CBRP Seed 6"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 6 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\6\cbrp\





echo "VSR 12 Seed 7"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\7\vsr_12\


echo "VSR 23 Seed 7"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 7 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\7\vsr_23\


echo "OLSR Seed 7"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\7\olsr\



echo "AODV Seed 7"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\7\aodv\



echo "CBRP Seed 7"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 7 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\7\cbrp\





echo "VSR 12 Seed 8"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\8\vsr_12\


echo "VSR 23 Seed 8"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 8 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\8\vsr_23\


echo "OLSR Seed 8"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\8\olsr\



echo "AODV Seed 8"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\8\aodv\



echo "CBRP Seed 8"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 8 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\8\cbrp\





echo "VSR 12 Seed 9"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\9\vsr_12\


echo "VSR 23 Seed 9"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 9 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\9\vsr_23\


echo "OLSR Seed 9"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\9\olsr\



echo "AODV Seed 9"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\9\aodv\



echo "CBRP Seed 9"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 9 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\9\cbrp\





echo "VSR 12 Seed 10"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\10\vsr_12\


echo "VSR 23 Seed 10"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 10 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\10\vsr_23\


echo "OLSR Seed 10"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\10\olsr\



echo "AODV Seed 10"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\10\aodv\



echo "CBRP Seed 10"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 10 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\10\cbrp\





echo "VSR 12 Seed 11"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\11\vsr_12\


echo "VSR 23 Seed 11"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 11 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\11\vsr_23\


echo "OLSR Seed 11"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\11\olsr\



echo "AODV Seed 11"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\11\aodv\



echo "CBRP Seed 11"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 11 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\11\cbrp\





echo "VSR 12 Seed 12"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\12\vsr_12\


echo "VSR 23 Seed 12"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 12 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\12\vsr_23\


echo "OLSR Seed 12"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\12\olsr\



echo "AODV Seed 12"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\12\aodv\



echo "CBRP Seed 12"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 12 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\12\cbrp\





echo "VSR 12 Seed 13"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\13\vsr_12\


echo "VSR 23 Seed 13"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 13 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\13\vsr_23\


echo "OLSR Seed 13"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\13\olsr\



echo "AODV Seed 13"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\13\aodv\



echo "CBRP Seed 13"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 13 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\13\cbrp\





echo "VSR 12 Seed 14"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\14\vsr_12\


echo "VSR 23 Seed 14"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 14 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\14\vsr_23\


echo "OLSR Seed 14"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\14\olsr\



echo "AODV Seed 14"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\14\aodv\



echo "CBRP Seed 14"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 14 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\14\cbrp\





echo "VSR 12 Seed 15"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\15\vsr_12\


echo "VSR 23 Seed 15"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 15 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\15\vsr_23\


echo "OLSR Seed 15"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\15\olsr\



echo "AODV Seed 15"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\15\aodv\



echo "CBRP Seed 15"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 15 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\15\cbrp\





echo "VSR 12 Seed 16"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\16\vsr_12\


echo "VSR 23 Seed 16"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 16 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\16\vsr_23\


echo "OLSR Seed 16"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\16\olsr\



echo "AODV Seed 16"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\16\aodv\



echo "CBRP Seed 16"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 16 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\16\cbrp\





echo "VSR 12 Seed 17"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\17\vsr_12\


echo "VSR 23 Seed 17"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 17 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\17\vsr_23\


echo "OLSR Seed 17"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\17\olsr\



echo "AODV Seed 17"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\17\aodv\



echo "CBRP Seed 17"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 17 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\17\cbrp\





echo "VSR 12 Seed 18"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\18\vsr_12\


echo "VSR 23 Seed 18"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 18 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\18\vsr_23\


echo "OLSR Seed 18"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\18\olsr\



echo "AODV Seed 18"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\18\aodv\



echo "CBRP Seed 18"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 18 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\18\cbrp\





echo "VSR 12 Seed 19"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\19\vsr_12\


echo "VSR 23 Seed 19"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 19 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\19\vsr_23\


echo "OLSR Seed 19"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\19\olsr\



echo "AODV Seed 19"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\19\aodv\



echo "CBRP Seed 19"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 19 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\19\cbrp\





echo "VSR 12 Seed 20"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	1	-k_cluster 2
move results_vsr\*.* a\routage-boundless\20\vsr_12\


echo "VSR 23 Seed 20"

op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 0.001		-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 5			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 10			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 15			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 20			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 25			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
op_runsim -net_name _vsr-40 -noprompt -ef vsr_mobility -SP_LOW_MAX 30			-seed 20 	-SP_LOW_MOBILITY_MODEL 3 	-k_cds	2	-k_cluster 3
move results_vsr\*.* a\routage-boundless\20\vsr_23\


echo "OLSR Seed 20"

op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 0.001		-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 5			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 10			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 15			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 20			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 25			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _olsr-40 -noprompt -ef olsr_mobility -SP_LOW_MAX 30			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
move results_olsr\*.* a\routage-boundless\20\olsr\



echo "AODV Seed 20"

op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 0.001		-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 5			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 10			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 15			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 20			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 25			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _aodv-40 -noprompt -ef aodv_mobility -SP_LOW_MAX 30			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
move results_aodv\*.* a\routage-boundless\20\aodv\



echo "CBRP Seed 20"

op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 0.001		-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 5			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 10			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 15			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 20			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 25			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
op_runsim -net_name _cbrp-40 -noprompt -ef cbrp_mobility -SP_LOW_MAX 30			-seed 20 	-SP_LOW_MOBILITY_MODEL 3
move results_cbrp\*.* a\routage-boundless\20\cbrp\





