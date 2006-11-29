#ifndef CDLC_HEADERS
	#define	CDCL_HEADERS

	

		/*----------------------------------------------------------------------
				     				Parameters		
		----------------------------------------------------------------------*/
		/* Special attribute values.			*/
		#define		TIME_INIT_MAC							5.0		//Time to wait before initialization
		#define		TIME_NETWORK_INIT						25.0	//All cumulated timers for initialization = 30 seconds
		#define		TIME_BEGIN_PERFS_STATS					20.0	//Time before starting collecting perfs_stats
		#define		TIME_BEGIN_STATS						50.0	//Time before starting collecting stats
		#define		TIME_BEGIN_DATA							60.0	//Time before starting sending data packets
		#define		TIME_BEGIN_TOPO_STATS					60.0
		#define		INTERVALL_STATS_COLLECTING				0.5
		#define		INTERVALL_QUICK_STATS_COLLECTING		0.05

		/*	General parameters	*/
		#define		MAX_NB_NODES							250
		#define		MAX_ADDRESS								300
		#define		MAX_NB_APS								2
		#define		MAX_NETWORK_RADIUS						15

		#define		PROCESS_NAME							"cds-cluster"

		// Network
		#define		PROMISCUOUS_FOR_UNICAST					0
		#define		BROADCAST								-1

		// Special Addresses (Multicast for APs...
		#define		LOWER_ADDR_FOR_MULTICAST				255			
		#define		ADDR_MULTICAST_AP						255
		#define		ADDR_MULTICAST_BACKBONE					256
		#define		ADDR_MULTICAST_BACKBONE_WITH_CONNECT	257
		#define		ADDR_MULTICAST_PAGING_MASTER			258
		#define		ADDR_INTERNET							200


		// To define Dimension of different structures
		#define		KCDS_MAX								10
		#define		KCLUSTER_MAX							20
		#define		NB_STORED_SPEEDS						20		//Keeps the NB_STORED_SPEEDS last speed values	

		#define		LOW_SPEED								1
		#define		HIGH_SPEED								2



		#define		ZERO									0


		/*----------------------------------------------------------------------
				     				NETWORK COMMON		
		----------------------------------------------------------------------*/

		/*	To distinguish different modules and functions for Stats	*/
		#define		HELLO							1
		#define		CDS								2
		#define		CLUSTER							3
		#define		OTHER							4		//For sleeping control for example
		#define		AP_HELLOS						5
		#define		BACKBONE_MULTICAST				6
		
		#define		DATA							10
		#define		ACK								11
		#define		RREQ							12
		#define		RREP							13
		#define		RERR							14



		/*----------------------------------------------------------------------
				     				CDS		
		----------------------------------------------------------------------*/

		/* States of CDS Creation */
		#define		DOMINATOR						1
		#define		DOMINATEE						2
		#define		ACTIVE							3
		#define		IDLE							0



		/*----------------------------------------------------------------------
										Packets			
		----------------------------------------------------------------------*/

		/*Type of packets */
		#define		HELLO_PK_TYPE					01
		#define		ACK_UNICAST_PK_TYPE				11
		//CDS Construction
		#define		CDS_MIS_PK_TYPE					20
		#define		CDS_JOIN_PK_TYPE				21
		#define		CDS_REVERSE_JOIN_PK_TYPE		22
		//CDS Maintenance
		#define		AP_HELLO_PK_TYPE				30
		#define		CDS_RECONNECT_PK_TYPE			31
		#define		CDS_RECON_REP_PK_TYPE			32
		#define		RECONNECT_INIT_PK_TYPE			33					
		#define		BREAK_CDS_PK_TYPE				34
		#define		NOTHING_NEIGH_CDS_PK_TYPE		35
		#define		USELESS_DOMINATOR_PK_TYPE		36					//To prevent our father that we have an idle neighbor (state=0)
		//Cluster Construction
		#define		HELLO_CLUSTER_PK_TYPE			40
		#define		JOIN_CLUSTER_PK_TYPE			41					//To declare That I am clusterhead
		//Cluster Maintenance
		#define		CON_CLUSTER_PK_TYPE				50
		#define		REP_CON_CLUSTER_PK_TYPE			51
		#define		HELLO_CLUSTERHEAD_PK_TYPE		52
		//Sleeping
		#define		SLEEPING_NODE_PK_TYPE			60
		//Control over backbone
		#define		BACKBONE_PK_TYPE				70
		#define		BACKBONE_WITH_CONNECT_PK_TYPE	71
		#define		AP_UNICAST_PK_TYPE				72
		

		//Higher Layer packet
		#define		DATA_PK_TYPE					80

		//Other pk type MUST be > DATA_PK_TYPE
		#define		ACK_APP_PK_TYPE					90
		#define		RREQ_PK_TYPE					91
		#define		RREP_PK_TYPE					92
		#define		RERR_PK_TYPE					93
		#define		RUPDATE_PK_TYPE					94
		#define		RDELETE_PK_TYPE					95
		
		//Paging Control
		#define		PAGING_REQ_PK_TYPE				100
		#define		PAGING_REP_PK_TYPE				101
		#define		PAGING_ACK_PK_TYPE				102
		#define		PAGING_DEL_PK_TYPE				103
		#define		PAGING_REP_GRATUITOUS_PK_TYPE	104

		//----------------------------------------------------------------------
		//			 	CODES FOR INTER-LEVEL COMMUNICATIONS
		//---------------------------------------------------------------------
		#define		DIE_CODE						201
		#define		STATE_CHANGE_CODE				202
		#define		SON_LOST_CODE					203

		//----------------------------------------------------------------------
		//			 	HIGHER LAYERS MANAGEMENT
		//---------------------------------------------------------------------
		#define		LOCALIZATION					1
		#define		ROUTING							2

		#define		LOCALIZATION_PROCESS_NAME		"somom"
		#define		ROUTING_PROCESS_NAME			"vsr"








		//----------------------------------------------------------------------
		//			     		Structures
		//---------------------------------------------------------------------
			


		//---------------------  Tables --------------------------------------


		//---------------------  Weight and Neighbourhood -----------------------------


		//Weight
		typedef struct {
			int 	value;
			int		last_neigh_changements[NB_STORED_SPEEDS][2];
			int		mobility;
			double	time_last_computation;
		//	short_neigh_cell*	last_neigh_table;
		} weight;


		//For the neighbourhood table
		typedef struct {
			int 	address;
			short 	hops;
			int		relay;
			double	timeout;
			short	bidirect;

			List*	neighbors;
			double	neighbors_timeout;
			
			int 	weight;
			int		mobility;
			short	sleep;
			
			int		state;
			int		father;
			short	father_hops;
			int		id_ap;
			short	ap_hops;
			int		clusterhead;
			short	clusterhead_hops;
			short	cluster_init_flag;		//Clustering is already initialized : we have received at least one cluster_hello from this node
			double	clusterhead_timeout;

			List*	gw_list;
			double	gw_timeout;

			struct neigh_cell *next;
		} neigh_cell;



		//For the short-neighbourhood table
		typedef struct {
			int 	address;
			short 	hops;
			struct  short_neigh_cell *next;
		} short_neigh_cell;


		typedef struct{
			char	address[40];
			char	weight[40];
			char	hops[40];
			char	state[40];
			char	bidirect[40];
			char	father[40];
			char	clusterhead[40];
		}struct_hello_field;

		//-----------------  For Wu & Li -----------------------


		//neighbors_list
		typedef struct{
			int		address;
			int		weight;
		} neigh_min;


		//To store Neighbor Table of Table
		typedef struct {
			int			address;
			int			weight;
			short		hops;
			double		timeout;
			Boolean		bidirect;
			List		*neighbors;	
		} neigh_wu;


		//---------------------  Utils ---------------------------------------

		//To store the id of packets already seen
		typedef struct{
			int		source; 		//the sender of packet
			int 	id;				//the correspondant id
			double	timeout;
			struct 	id_cell *next;
		}id_cell;



		//The retransmission table (for acks)
		typedef struct{
			int		id;
			float	timeout;
			Packet	*packet;
			short	nb_retry;					//The number of tentatives
			struct 	ret_cell *next;
		}ret_cell;


		//Short commutation table (for control messages)
		typedef struct{
			int		src;
			int		relay;
			float	timeout;
			struct 	relay_cell *next;
		} relay_cell;
		//It's a very short routing table in order to forward multihops packets in unicast


		//Multiple Ici (one for each packet)
		typedef struct{
			Ici*	ici_ptr;
			double	timeout;
		} struct_ici;




		//---------------------  Energy ---------------------------------------

		//infos about the die
		typedef struct{
			short	bool;
			double	time;
		} dead_struct;


		//Energy
		typedef struct {
			double			value;				//Energy : all values are in microWatts (1/1000 mWatts)
			double			initial_value;
			double			max_capacity;
			double			min_capacity;
			double			previous_value;
		} energy_struct;


		//Sleeping
		typedef struct {
			short			value;
			double			time_sleeping;
			double			cumul_sleeping_time;
		} sleeping_struct;


		//Stat about energy Consumption
		typedef struct{
			double		energy;
			double		time;
		} energy_stats_stuct;



		//--------------------- Geography ---------------------------------------

		//X and Y Positions
		typedef struct{
			double		x;
			double		y;	
		} coordinates;


		//---------------------  Sons / Dominatees ---------------------------------------

		//Sons and dominatees
		typedef struct{
			int			address;
			struct son *next;
		} son;

		typedef struct{
			int			address;
			struct dominatee *next;
		} dominatee;


		//---------------------  CDS -------------------------------------

		//Define the list of last seen ap hellos and their trasnmitters
		typedef struct{
			int		address;
			float	last_seen;
			int		id_ap;
			int		id_hello;
			struct	ap_hellos		*next;
		} ap_hellos;


		typedef struct{
			int 		address;
			int			weight;
			float		last_seen;
			int			parent;			//The clusterhead or the father (depend from the case)
			Packet*		pk;
			struct candidate	*next;
		} candidate;

		typedef struct{
			int		address;
			int		id_ap;
			short	state;
			double	timeout;
		} struct_cds_connector;

		//CDS
		typedef struct{
			int				father;
			short			father_hops;
			int				id_ap;
			short			ap_hops;
			int				relay;
			double			relay_timeout;
			short			state;
			double			previous_state_change_time;
			son				*sons;
			dominatee		*dominatees;
			List			*cds_connectors_list;

			Boolean			is_maintenance_scheduled;
			double			last_join_message_sent;
			short			join_already_forwarded[2*KCLUSTER_MAX-KCDS_MAX+1];			// T[i]=1 if a join message with TTL>=i+1 was already forwarded by this dominatee // =0 else    	
			short			cds_intrpt_end;
			short			nb_retry_reconnect_cds;

			float			last_hello_ap_seen; 
			int				id_last_hello_ap_seen;				
			int				current_id_ap_hello;
			
			candidate*		secondary_fathers;
			
			double			time_dominator_usefull;
			float			time_last_break;
			float			time_cds_reinit;
			float			time_last_cds_reconstruct;
		} cds;




		//---------------------- Clusters ----------------------------------

		//For the cluster table
		typedef struct {
			int 	address;
			int 	weight;
			short 	hops;
			double	timeout;
			int		clusterhead;
			struct cluster_cell *next;
		} cluster_cell;



		typedef struct{
			int			address;
			int			relay;
			short		hops;
			double		relay_last_seen;
			double		time_last_break;
			int			last_id;
			short		nb_recon_try;
			candidate*	reconnect_candidates;
			double		last_inscription;
			double		last_time_usefull;
			double		last_seen;
			short		construct_cluster;
		} clusterhead;


		//---------------------- Acks ----------------------------------

		typedef struct{
			double		time_sent;
			int			dest;
			Packet*		pk;
			int			nb_retransmits;
			struct ack_cell	*next;
		} ack_cell;

		typedef struct{
			List*		dest_list;
			Packet*		pk;
			int			pk_id;
			double		timeout;
			int			nb_retry;
		} struct_ack_multicast;


		//----------------------------------------------------------------------
		//							STATS
		//----------------------------------------------------------------------

		typedef struct{
			Boolean		is_dominator [MAX_NB_NODES];
			Boolean		is_rcvd		 [MAX_NB_NODES];
			double		time_emission;
			double		time_reception;
		} struct_bb_flooding;


		typedef struct{
			int			source;
			int			dest;
			int			hops;
			double		time_emission;
			double		time_reception;
		} struct_ap_unicast;

		
		typedef struct{
			int			nb_parents;
			int			nb_cds_connectors;
		} struct_stats;

		//----------------------------------------------------------------------
		//						Study of Stability 			
		//----------------------------------------------------------------------

		//Table with informations about topology of clusters
		typedef struct{
			int 		cluster1;
			int 		cluster2;
			float		last;			
			struct cl_neigh_global	*next;
		} cl_neigh_global;
		cl_neigh_global			*cluster_topo;


		//Structures to store the old information about clusterhead, old cluster (as gateway)
		typedef struct{
			int 		addr;
			float		last;			
			struct list	*next;
		} list;


		typedef struct{
			list	*gw;
			list	*clusters;
			int		old_clusterhead;
		} old_cl_topo;





#endif