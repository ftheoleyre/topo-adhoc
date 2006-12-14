op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 0.001			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 5			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 10			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 15			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 20			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 25			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_mobility -SP_LOW_MAX 30			-seed xxx
move results_localization\*.* a\mobility\seriexxx\somom\
move results\*.* a\mobility\seriexxx\somom\cdcl\
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 0.001		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 5			-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 10			-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 15			-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 20			-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 25			-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_mobility -SP_LOW_MAX 30			-seed xxx
move results_mewlana\*.* a\mobility\seriexxx\mewlana\



op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 1		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 3		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 5		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 10		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 20		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 30		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_connections -NB_CONNECTIONS 40		-seed xxx
move results_localization\*.* a\nb_connections\seriexxx\somom\
move results\*.* a\nb_connections\seriexxx\somom\cdcl\
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 1		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 3		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 5		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 10		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 20		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 30		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_connections -NB_CONNECTIONS 40		-seed xxx
move results_mewlana\*.* a\nb_connections\seriexxx\mewlana\



op_runsim -net_name _somom-10 -noprompt -ef somom_nb_nodes -X_MAX 500  -Y_MAX 500		-seed xxx
op_runsim -net_name _somom-20 -noprompt -ef somom_nb_nodes -X_MAX 1100 -Y_MAX 1100		-seed xxx
op_runsim -net_name _somom-30 -noprompt -ef somom_nb_nodes -X_MAX 1700 -Y_MAX 1700		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_nb_nodes -X_MAX 2100 -Y_MAX 2100		-seed xxx
op_runsim -net_name _somom-50 -noprompt -ef somom_nb_nodes -X_MAX 2350 -Y_MAX 2350		-seed xxx
op_runsim -net_name _somom-60 -noprompt -ef somom_nb_nodes -X_MAX 2550 -Y_MAX 2550		-seed xxx
move results_localization\*.* a\nb_nodes\seriexxx\somom\
move results\*.* a\nb_nodes\seriexxx\somom\cdcl
op_runsim -net_name _mewlana-10 -noprompt -ef mewlana_nb_nodes -X_MAX 500  -Y_MAX 500		-seed xxx
op_runsim -net_name _mewlana-20 -noprompt -ef mewlana_nb_nodes -X_MAX 1100 -Y_MAX 1100		-seed xxx
op_runsim -net_name _mewlana-30 -noprompt -ef mewlana_nb_nodes -X_MAX 1700 -Y_MAX 1700		-seed xxx
op_runsim -net_name _mewlana-40 -noprompt -ef mewlana_nb_nodes -X_MAX 2100 -Y_MAX 2100		-seed xxx
op_runsim -net_name _mewlana-50 -noprompt -ef mewlana_nb_nodes -X_MAX 2350 -Y_MAX 2350		-seed xxx
op_runsim -net_name _mewlana-60 -noprompt -ef mewlana_nb_nodes -X_MAX 2550 -Y_MAX 2550		-seed xxx
move results_mewlana\*.* a\nb_nodes\seriexxx\mewlana\



op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 1	-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 0.8	-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 0.6	-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 0.4	-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 0.2	-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_intern_com -INTERN_COMMUNICATIONS_RATIO 0	-seed xxx
move results\*.* a\intern_com\seriexxx\somom\cdcl\
move results_localization\*.* a\intern_com\seriexxx\somom\



op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 0.001		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 5		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 10		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 15		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 20		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 25		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_mobility -SP_LOW_MAX 30		-seed xxx
move results_localization\*.* a\pag_mob\seriexxx\somom\
move results\*.* a\pag_mob\seriexxx\somom\cdcl\



op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 1		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 5		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 10		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 15		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 20		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 30		-seed xxx
op_runsim -net_name _somom-40_2AP -noprompt -ef somom_paging_load -NB_CONNECTIONS 40		-seed xxx
move results_localization\*.* a\pag_load\seriexxx\somom\
move results\*.* a\pag_load\seriexxx\somom\cdcl\



op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 0.001		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 5			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 10		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 15		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 20		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 25		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_mobility -SP_LOW_MAX 30		-seed xxx
move results_localization\*.* a\en_mob\seriexxx\somom\
move results\*.* a\en_mob\seriexxx\somom\cdcl\



op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 1			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 5			-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 10		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 15		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 20		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 30		-seed xxx
op_runsim -net_name _somom-40 -noprompt -ef somom_energy_load -NB_CONNECTIONS 40		-seed xxx
move results_localization\*.* a\en_load\seriexxx\somom\
move results\*.* a\en_load\seriexxx\somom\cdcl\

