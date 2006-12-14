
echo "WU&LI Seed xxx"

op_runsim -net_name _cdcl-20 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385		-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\20\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\20\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\20\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\20\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\20\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\20\routes_hybrid.txt

op_runsim -net_name _cdclr-30 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\30\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\30\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\30\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\30\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\30\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\30\routes_hybrid.txt

op_runsim -net_name _cdcl-40 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960		-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\40\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\40\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\40\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\40\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\40\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\40\routes_hybrid.txt

op_runsim -net_name _cdclr-50 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\50\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\50\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\50\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\50\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\50\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\50\routes_hybrid.txt

op_runsim -net_name _cdcl-60 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400		-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\60\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\60\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\60\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\60\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\60\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\60\routes_hybrid.txt

op_runsim -net_name _cdcl-70 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592		-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\70\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\70\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\70\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\70\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\70\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\70\routes_hybrid.txt

op_runsim -net_name _cdcl-80 -noprompt 	-ef wu_li_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771		-seed xxx 	-k_cds	1
copy results\*bps*.* a\topo\xxx\wu_li_cds\80\graph_bps.txt
move results\*cds_ad_hoc*.* a\topo\xxx\wu_li_cds\80\routes_ad_hoc.txt
move results\*cds_hybrid*.* a\topo\xxx\wu_li_cds\80\routes_hybrid.txt
move results\*bps*.* a\topo\xxx\wu_li_direct\80\graph_bps.txt
move results\*direct_ad_hoc*.* a\topo\xxx\wu_li_direct\80\routes_ad_hoc.txt
move results\*direct_hybrid*.* a\topo\xxx\wu_li_direct\80\routes_hybrid.txt




echo "VSR 12 Seed xxx"

op_runsim -net_name _vsr-20 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\20\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\20\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\20\routes_hybrid.txt
op_runsim -net_name _vsr-30 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\30\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\30\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\30\routes_hybrid.txt
op_runsim -net_name _vsr-40 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\40\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\40\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\40\routes_hybrid.txt
op_runsim -net_name _vsr-50 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\50\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\50\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\50\routes_hybrid.txt
op_runsim -net_name _vsr-60 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\60\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\60\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\60\routes_hybrid.txt
op_runsim -net_name _vsr-70 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\70\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\70\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\70\routes_hybrid.txt
op_runsim -net_name _vsr-80 -noprompt 	-ef vsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 	-k_cds	1	-k_cluster 2
move results\*bps*.* a\topo\xxx\vsr_12\80\graph_bps.txt
move results\*ad_hoc*.* a\topo\xxx\vsr_12\80\routes_ad_hoc.txt
move results\*hybrid*.* a\topo\xxx\vsr_12\80\routes_hybrid.txt






echo "OLSR Seed xxx"

op_runsim -net_name _olsr-20 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1385 -Y_MAX 1385	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\20\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\20\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\20\routes_hybrid.txt
op_runsim -net_name _olsr-30 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1697 -Y_MAX 1697	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\30\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\30\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\30\routes_hybrid.txt
op_runsim -net_name _olsr-40 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 1960 -Y_MAX 1960	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\40\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\40\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\40\routes_hybrid.txt
op_runsim -net_name _olsr-50 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2191 -Y_MAX 2191	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\50\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\50\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\50\routes_hybrid.txt
op_runsim -net_name _olsr-60 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2400 -Y_MAX 2400	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\60\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\60\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\60\routes_hybrid.txt
op_runsim -net_name _olsr-70 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2592 -Y_MAX 2592	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\70\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\70\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\70\routes_hybrid.txt
op_runsim -net_name _olsr-80 -noprompt 	-ef olsr_topo_nb_nodes -X_MAX 2771 -Y_MAX 2771	-seed xxx 
move results_olsr\*bps*.* a\topo\xxx\olsr\80\graph_bps.txt
move results_olsr\*ad_hoc*.* a\topo\xxx\olsr\80\routes_ad_hoc.txt
move results_olsr\*hybrid*.* a\topo\xxx\olsr\80\routes_hybrid.txt
