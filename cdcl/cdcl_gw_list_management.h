#ifndef CDLC_GW_HEADERS
	#define	CDCL_GW_HEADERS


	//Structures
	typedef struct{
		int			cluster;
	} struct_gw;


	Boolean		cluster_present_in_gw_list(int address , List* gw_list);
	void		add_in_gw_list(int address, List* gw_list);
	void		empty_gw_list(List* gw_list);
	void		print_gw_list(List* gw_list);



#endif