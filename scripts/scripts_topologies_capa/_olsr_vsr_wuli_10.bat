
echo "WU&LI Seed 1"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 1 	-k_cds	1
copy results\*bps*.* a\topo\1\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\1\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\1\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\1\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\1\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\1\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 1"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 1 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\1\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\1\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\1\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 1"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 1 
move results_olsr\*bps*.* a\topo\1\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\1\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\1\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 2"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 2 	-k_cds	1
copy results\*bps*.* a\topo\2\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\2\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\2\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\2\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\2\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\2\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 2"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 2 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\2\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\2\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\2\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 2"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 2 
move results_olsr\*bps*.* a\topo\2\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\2\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\2\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 3"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 3 	-k_cds	1
copy results\*bps*.* a\topo\3\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\3\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\3\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\3\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\3\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\3\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 3"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 3 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\3\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\3\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\3\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 3"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 3 
move results_olsr\*bps*.* a\topo\3\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\3\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\3\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 4"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 4 	-k_cds	1
copy results\*bps*.* a\topo\4\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\4\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\4\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\4\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\4\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\4\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 4"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 4 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\4\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\4\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\4\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 4"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 4 
move results_olsr\*bps*.* a\topo\4\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\4\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\4\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 5"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 5 	-k_cds	1
copy results\*bps*.* a\topo\5\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\5\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\5\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\5\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\5\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\5\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 5"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 5 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\5\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\5\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\5\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 5"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 5 
move results_olsr\*bps*.* a\topo\5\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\5\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\5\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 6"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 6 	-k_cds	1
copy results\*bps*.* a\topo\6\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\6\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\6\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\6\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\6\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\6\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 6"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 6 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\6\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\6\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\6\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 6"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 6 
move results_olsr\*bps*.* a\topo\6\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\6\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\6\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 7"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 7 	-k_cds	1
copy results\*bps*.* a\topo\7\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\7\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\7\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\7\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\7\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\7\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 7"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 7 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\7\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\7\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\7\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 7"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 7 
move results_olsr\*bps*.* a\topo\7\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\7\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\7\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 8"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 8 	-k_cds	1
copy results\*bps*.* a\topo\8\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\8\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\8\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\8\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\8\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\8\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 8"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 8 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\8\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\8\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\8\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 8"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 8 
move results_olsr\*bps*.* a\topo\8\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\8\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\8\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 9"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 9 	-k_cds	1
copy results\*bps*.* a\topo\9\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\9\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\9\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\9\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\9\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\9\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 9"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 9 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\9\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\9\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\9\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 9"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 9 
move results_olsr\*bps*.* a\topo\9\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\9\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\9\olsr\80\routes_hybrid.txt






echo "WU&LI Seed 10"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed 10 	-k_cds	1
copy results\*bps*.* a\topo\10\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\10\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\10\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\10\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\10\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\10\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed 10"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 10 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\10\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\10\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\10\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed 10"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed 10 
move results_olsr\*bps*.* a\topo\10\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\10\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\10\olsr\80\routes_hybrid.txt





