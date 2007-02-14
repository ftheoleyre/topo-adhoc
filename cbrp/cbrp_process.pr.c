/* Process model C form file: cbrp_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char cbrp_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 45BF2633 45BF2633 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

#if defined (__cplusplus)
extern "C" {
#endif
FSM_EXT_DECS
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif


/* Header Block */

/* Include files.					*/
#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>


/*----------------------------------------------------------------------
				     		Parameters		
----------------------------------------------------------------------*/

/* Special attribute values.			*/
#define		TIME_INIT_MAC					5.0		//Time to wait before initialization
#define		TIME_BEGIN_STATS				15.0
#define		TIME_BEGIN_DATA					60.0	//Time to wait before sending data packets
#define		TIME_BEGIN_NETWORK				40.0
#define		BROADCAST						-1
#define		PROCESS_ID_NAME					"cbrp"

/*	General parameters	*/
#define		MAX_NETWORK_RADIUS				10
#define		MAX_NB_NODES					150
#define		INTERVALL_HELLO_CH				2.0
#define		MAX_ADDRESS						160
#define		LOW_SPEED						1
#define		HIGH_SPEED						2
#define		PROMISCUOUS_FOR_UNICAST			0


/*	For automatic attribution of Addresses		*/
#define		ADDR_RANDOM						0
#define		ADDR_WLAN						1
#define		ADDR_CONFIGURED					2
#define		ADDR_MAC_CDCL_FROM_NAME			3
	

/* Special Addresses (Multicast for APs...) */
#define		ADDR_MULTICAST_AP				255
#define		ADDR_MULTICAST_BACKBONE			256
#define		LOWER_ADDR_FOR_MULTICAST		255			


/* Intervalls for packets and interruptions */
#define		INTERVALL_HELLO					4.0
#define		INTERVALL_PERIODIC_FUNCTIONS	1.0


/*  Timeouts  */
#define		TIMEOUT_HELLO					3.1			//In Hellos-intervals
#define		TIMEOUT_HELLO_CH				2.1
#define		TIMEOUT_USELESS_CH				4.1			//How long time I must wait before declaring myself client (since I am an useless clusterhead)
#define		TIMEOUT_UNICAST_ACK				0.2			//Acks in Unicast
#define		TIMEOUT_ADDR_PK_ID				20.1
#define		TIMEOUT_ICI						1.0
#define		TIMEOUT_ROUTE					10
#define		TIMEOUT_DATA_PK_BUFFER			1.0
#define		TIMEOUT_RREQ_PK_BUFFER			0.5

/* HELLOS */
#define		MAX_FIELDS_IN_HELLO				60			//From 0 to 60
#define		MAX_CLUSTER_FIELDS_IN_HELLO		11			//From 0 to 10


/* RREQ */
#define		MAX_RELAY_FIELDS_IN_RREQ_PK		16
#define		MAX_RREQ_PK						100000
#define		MAX_CLUSTER_FIELDS_IN_RREQ_PK	15
#define		MAX_NB_RREQ_RETRY				3

/* DATA */
#define		MAX_DATA_PK						100000

#define		MAX_NB_LOCAL_REPAIRS_FOR_DATA	3
#define		MAX_NB_REPAIRS_FOR_ONE_NODE		1


/* Acks	*/
#define		MAX_NB_RETRIES_UNICAST_ACKS		2
#define		ACK_FOR_RREP					0
#define		ACK_FOR_RERR					0

/* RERR */
#define		MAX_RERR_PK						100000


/* Figures for Topology */
#define		THICKNESS_PHYSIC_NEIGHBOR		2
#define		COLOR_AP_CONNECTED				6
#define		COLOR_AP_DISCONNECTED			0
#define		GRAPHIC_XMAX					9000




/*----------------------------------------------------------------------
						PACKETS			
----------------------------------------------------------------------*/
//Streams
#define		STRM_FROM_WLAN					0
#define		STRM_TO_WLAN					0

#define		STRM_FROM_ETH					2
#define		STRM_TO_ETH						2

#define		STRM_FROM_HIGHER	   			1
#define		STRM_TO_HIGHER					1


//For Stats
#define		UNICAST_ACK						3
#define		HELLO							4
#define		DATA							5
#define		RREQ							6
#define		RREP							7
#define		RERR							8


//Packets Type
#define		UNICAST_ACK_PK_TYPE				3
#define		HELLO_PK_TYPE					4
#define		DATA_PK_TYPE					5
#define		RREQ_PK_TYPE					6
#define		RREP_PK_TYPE					7
#define		RERR_PK_TYPE					8





/*----------------------------------------------------------------------
						Interruptions			
----------------------------------------------------------------------*/

/* Interruption codes */
#define		HELLO_GENERATE_CODE				2
#define		PK_DATA_GENERATE_CODE			3
//#define		PK_RREQ_GENERATE_CODE			4

#define		PERIODIC_FUNCTIONS_CODE			10
#define		UNICAST_RETRANSMISSIONS_CODE	11
#define		WRITE_TOPOLOGY_CODE				12

#define		CLUSTER_CONSTRUCTION_CODE		20
#define		CLUSTER_MAINTENANCE_CODE		21

#define		RREQ_SEND_TIMEOUT_CODE			31

/* Macro definitions for state		*/
/* transitions.						*/
#define		ENDSIM							(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define 	PK_FROM_ETH						(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_ETH)
#define 	PK_FROM_WLAN					(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_WLAN)
#define		PK_FROM_LOWER					(PK_FROM_ETH || PK_FROM_WLAN)
#define 	PK_DATA_GENERATE				(op_intrpt_code() == PK_DATA_GENERATE_CODE)
#define		PERIODIC_FUNCTIONS				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == PERIODIC_FUNCTIONS_CODE)
#define		UNICAST_RETRANSMISSIONS			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == UNICAST_RETRANSMISSIONS_CODE)
#define		CLUSTER							(op_intrpt_type() == OPC_INTRPT_SELF  ) && ((op_intrpt_code() == CLUSTER_CONSTRUCTION_CODE) || (op_intrpt_code() == CLUSTER_MAINTENANCE_CODE))







/*----------------------------------------------------------------------
						Structures
----------------------------------------------------------------------*/


//-------- PK BUFFERING ---------

//Data Pk Buffer
typedef struct{
	Packet	*packet;
	int		dest;
	double	timeout;
} struct_pk_buffer;


//RREQ Pk Buffer (We must add nb of retries)
typedef struct{
	int		dest;
	int		stat_id;
	double	timeout;
	int		nb_retry;
} struct_rreq_pk_buffer;





//-------- PK COMMON MANAGEMENT ---------

//For Addr/Pk_id records
typedef struct {
	int			address;
	int			pk_id;
	double		timeout;
} struct_addr_pk_id;


//Acks table
typedef struct{
	int			dest;
	int			pk_id;
	double 		timeout;
	short		nb_retry;
	short		nb_repairs;
	packet*		pkptr;	
} struct_ack;


//Multiple Ici (one for each packet)
typedef struct{
	Ici*	ici_ptr;
	double	timeout;
} struct_ici;




//-------- ROUTING ---------

//Routing Table
typedef struct{
	int 		dest;
	int			relay;
	short		hops;
	int			weight;
	int			clusterhead;
	double		timeout;
	Boolean		bidirect;
	List		*neighbors;
	List		*route;
} struct_routing ;



//-------- CLUSTERS ---------

//Cluster
typedef struct{
	int					clusterhead;
	int					my_weight;
	double				last_time_usefull;
} struct_cluster;


//Cluster Neighbors for Clusterhead
typedef struct{
	int		cluster;
	int		gw;
	double	timeout;
} struct_cl_neigh;





/*----------------------------------------------------------------------
						Structures For Stats Collect
----------------------------------------------------------------------*/

//----------------------------------------------------------------------
//						Structures For Stats Collect
//----------------------------------------------------------------------


//DATA PK
typedef struct{
	int		source;
	int		dest;
	int		pk_size;
	short	hops;
	int		nb_retry;
	int		nb_repairs;
	double	time_generation;
	double	time_emission;
	double	time_reception;
	short	method;
	double	src_x_pos;
	double	src_y_pos;
	double	dest_x_pos;
	double	dest_y_pos;
	char	route[100];
} struct_stats_data;


//RREQ/RREP PK
typedef struct{
	int			source;
	int			dest;
	Boolean		rreq_is_ch[MAX_NB_NODES];
	Boolean		rreq_is_rcvd[MAX_NB_NODES];
	double		rreq_time_emission;
	double		rreq_time_reception;
	int			rreq_nb_retry;
	double		rrep_time_emission;
	double		rrep_time_reception;
	int			rrep_hops;
	int			rrep_nb_retry;
	Boolean		rrep_is_gratuitous;
} struct_stats_rreq;

//RERR PK
typedef struct{
	int		source;
	int		dest;
	int		data_dest;
	int		nb_retry;
	int		hops;
	double	time_emission;
	double	time_reception;
} struct_stats_rerr;


//CLUSTERS
typedef struct{
	int		my_clusterhead;
}struct_stats_cluster;


/*----------------------------------------------------------------------
	     		Global Variables for Control		
----------------------------------------------------------------------*/

/*	Common	*/
int			begin_time 				= 0;
int			current_nb_connections	= 0;

/* Nb nodes, special nodes... */
int			nb_nodes 			= 0;
int			nb_nodes_expected 	= 0;
int			nb_aps	 			= 0;
int			nb_aps_expected		= 0;

/* Speeds */
int			nb_high_speed_nodes = 0;
int			nb_low_speed_nodes 	= 0;

/* Degree */
int			average_degree = 0;





/*----------------------------------------------------------------------
				     		Statistics		
----------------------------------------------------------------------*/
//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];

//Topology Figures
short		stats_nb_position_written;
short		stats_positions		[MAX_NB_NODES][2];						//1- x-coordinate, 2- y-coordinate, 
short		stats_links			[MAX_NB_NODES][MAX_NB_NODES];			//[i][j] 1 If there exists a link between nodes i and j




/*----------------------------------------------------------------------
			     		Packet Statistics		
----------------------------------------------------------------------*/

int			nb_pk_unicast_ack_instantaneous 					= 0;
int			nb_pk_unicast_ack_total 							= 0;

int			nb_pk_hello_instantaneous 							= 0;
int			nb_pk_hello_total 									= 0;

int			nb_pk_data_instantaneous 							= 0;
int			nb_pk_data_total 									= 0;
int			nb_pk_data_retransmission_instantaneous 			= 0;
int			nb_pk_data_retransmission_total 					= 0;

int			nb_pk_rreq_instantaneous 							= 0;
int			nb_pk_rreq_total 									= 0;

int			nb_pk_rrep_instantaneous 							= 0;
int			nb_pk_rrep_total 									= 0;
int			nb_pk_rrep_retransmission_instantaneous 			= 0;
int			nb_pk_rrep_retransmission_total 					= 0;

int			nb_pk_rerr_instantaneous 							= 0;
int			nb_pk_rerr_total 									= 0;
int			nb_pk_rerr_retransmission_instantaneous 			= 0;
int			nb_pk_rerr_retransmission_total 					= 0;



/*----------------------------------------------------------------------
			     		Clusters		
----------------------------------------------------------------------*/
int			stats_nb_ch_changes									= 0;		//Nb of clusterhead wich become clients
int			stats_nb_ch_clients_changes							= 0;		//Nb of clients which change their clusterhead
int			stats_nb_neighbors_changes							= 0;		//Comparison : 	physic changes
int			stats_nb_virtual_changes							= 0;		//				virtual changes (cluster topology)
int			stats_average_nb_of_ch								= 0;
struct_stats_cluster		stats_cluster	[MAX_NB_NODES];


/*----------------------------------------------------------------------
						    Data 	Packets		
----------------------------------------------------------------------*/
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;
int			current_id_data 		= 0;



/*----------------------------------------------------------------------
					    RREQ / RREP 	Packets		
----------------------------------------------------------------------*/
struct_stats_rreq	stats_rreq	[MAX_RREQ_PK];

int		stats_nb_rreq 				= 0;
int		stats_nb_rrep				= 0;
int		stats_nb_pk_for_all_rreq	= 0;

/*----------------------------------------------------------------------
					   RERR	
----------------------------------------------------------------------*/
struct_stats_rerr	stats_rerr			[MAX_RERR_PK];
int			stats_nb_rerr 				= 0;


/*----------------------------------------------------------------------
			     		Clusters   GLOBAL TOPOLOGY	
----------------------------------------------------------------------*/

typedef struct{
	int		src;
	int		addr1;
	int		addr2;
	double	timeout;
} struct_stats_cl;

typedef struct {	
	int		cluster;
	double	timeout;
} struct_cluster_gw;

List*		stats_cluster_global;







/*----------------------------------------------------------------------
						Functions Prototypes
----------------------------------------------------------------------*/

//Packet
Boolean addr_pk_id_not_seen (int addr , int pk_id);
void 	pk_send_delayed(Packet* pkptr , double delay);
void 	pk_send(Packet* pkptr);
void 	add_address_id_couple(int addr , int pk_id);

//Debug
void 	cbrp_debug(char* msg);
void 	cbrp_data(char* msg);
void 	cbrp_rreq(char* msg);
void 	cbrp_rrep(char* msg);
void 	cbrp_rerr(char* msg);
void 	cbrp_test(char* msg);

void 	print_routing_table();
void 	print_routes();
void 	print_ack_table();
void 	print_stats_cluster_local();
void 	print_stats_cluster_global();
void 	print_neighbors();
void 	print_rreq_pk_buffer();


//Routing Table
void 	add_routing_entry (int dest, int relay , short hops , int weight , int clusterhead , double timeout , Boolean bidirect , List* list_neighbors , List* route);
void 	delete_timeout_in_routing_table ();
int 	get_relay_in_routing_table (int dest);
List*	create_list_of_neighbors_from_hello_packet(Packet* pkptr);
double	timeout_routing_entry (int address);

//Acks
void	add_unicast_ack(int dest , int pk_id , Packet* pkptr);

//Hellos
void 	update_neighbors (Packet* pkptr);


//Management of list of Gateways, and Cluster Neighbors
//For Clusterheads
void	add_cluster_neighbor_gw (int gw , int cluster);
void	delete_timeout_in_cluster_neighbor_gw();
void	delete_specific_gw_in_cluster_neighbor_gw(int addr);
//For Gateways
void 	delete_timeout_in_cluster_gw();
void 	add_cluster_gw(int addr);
void 	delete_all_in_cluster_gw();
void	update_cluster_gw();

//Comon Control
Boolean is_integer_present_in_list(List* list, int value);
Boolean add_integer_in_list(List* list, int value);

//RREQ / RREP
void 	send_rreq(int final_dest);							//The first RREQ Generation (packet + buffer)
void 	send_rreq_pk(int final_dest, int stat_rreq_id);		//RREQ generation (only the packet)
void 	send_rrep(Packet* pk_src);

//DATA
void 	send_data(int dest , int code);
int		set_dest_data_to_next_relay(Packet* pk_dest);

/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(last_line_passed) = __LINE__ - _block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(last_line_passed) = 0; _block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	int	                    		my_address;
	short	                  		DEBUG;
	int	                    		current_id;
	int	                    		my_stat_id;
	List*	                  		addr_pk_id_list;
	List*	                  		routing_table;
	List*	                  		ack_table;
	Distribution *	         		distrib;
	Boolean	                		DEBUG_DATA;
	Boolean	                		DEBUG_LOAD;
	struct_cluster	         		my_cluster;
	List*	                  		stats_cluster_local;
	List*	                  		cluster_gw;
	List*	                  		cluster_neighbors;
	List*	                  		ici_list;
	Boolean	                		DEBUG_CONTROL;
	int	                    		DEBUG_TOPO;
	List*	                  		data_pk_buffer;
	List*	                  		rreq_pk_buffer;
	int	                    		NB_CONNECTIONS;
	int	                    		DATA_PK_SIZE;
	int	                    		NB_PK_PER_FLOW;
	double	                 		INTERARRIVAL_DATA_PK;
	int	                    		is_AP;
	int	                    		ACK_FOR_DATA;
	} cbrp_process_state;

#define pr_state_ptr            		((cbrp_process_state*) SimI_Mod_State_Ptr)
#define my_address              		pr_state_ptr->my_address
#define DEBUG                   		pr_state_ptr->DEBUG
#define current_id              		pr_state_ptr->current_id
#define my_stat_id              		pr_state_ptr->my_stat_id
#define addr_pk_id_list         		pr_state_ptr->addr_pk_id_list
#define routing_table           		pr_state_ptr->routing_table
#define ack_table               		pr_state_ptr->ack_table
#define distrib                 		pr_state_ptr->distrib
#define DEBUG_DATA              		pr_state_ptr->DEBUG_DATA
#define DEBUG_LOAD              		pr_state_ptr->DEBUG_LOAD
#define my_cluster              		pr_state_ptr->my_cluster
#define stats_cluster_local     		pr_state_ptr->stats_cluster_local
#define cluster_gw              		pr_state_ptr->cluster_gw
#define cluster_neighbors       		pr_state_ptr->cluster_neighbors
#define ici_list                		pr_state_ptr->ici_list
#define DEBUG_CONTROL           		pr_state_ptr->DEBUG_CONTROL
#define DEBUG_TOPO              		pr_state_ptr->DEBUG_TOPO
#define data_pk_buffer          		pr_state_ptr->data_pk_buffer
#define rreq_pk_buffer          		pr_state_ptr->rreq_pk_buffer
#define NB_CONNECTIONS          		pr_state_ptr->NB_CONNECTIONS
#define DATA_PK_SIZE            		pr_state_ptr->DATA_PK_SIZE
#define NB_PK_PER_FLOW          		pr_state_ptr->NB_PK_PER_FLOW
#define INTERARRIVAL_DATA_PK    		pr_state_ptr->INTERARRIVAL_DATA_PK
#define is_AP                   		pr_state_ptr->is_AP
#define ACK_FOR_DATA            		pr_state_ptr->ACK_FOR_DATA

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	cbrp_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   NEIGHBORHOOD
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Computes my weight
int my_weight(){
	return (255 * (nb_nodes - my_stat_id) / nb_nodes);
}


//Generate an hello packet
void hello(int useless_arg, int code){
	//Packet
	Packet*				pkptr;
	//Routing Table
	struct_routing*		routing_entry;	
	//For each Neighbors in packet
	int					field_num = 0;
	char				neighbor_name[200];	
	char				bidirect_name[200];	
	char				cluster_name[200];	
	//Control
	char				msg[1000];
	int					i;
	//Cluster GWs
	struct_cluster_gw*	cl_entry;
			
	//Update my weight
	my_cluster.my_weight = my_weight();
	
	//Prepare the packet
	pkptr = op_pk_create_fmt ("cbrp_hello");
	op_pk_nfd_set(pkptr,"SRC",			my_address);
	op_pk_nfd_set(pkptr,"DEST",			-1);

	op_pk_nfd_set(pkptr,"WEIGHT",		my_cluster.my_weight);
	op_pk_nfd_set(pkptr,"CLUSTERHEAD",	my_cluster.clusterhead);

	op_pk_nfd_set(pkptr,"PK_ID",		current_id++);	
	op_pk_nfd_set(pkptr,"TTL",			1);
	op_pk_nfd_set(pkptr,"OPTION_TYPE",	HELLO_PK_TYPE);
		
		
	if (DEBUG>6) 
		{
			sprintf(msg,"I send an hello (id=%d) at %f\n" , current_id-1 , op_sim_time());
			cbrp_debug (msg);
		}	
	
//LIST OF NEIGHBORS	
	//We add all 1-neighbors
	field_num = 0;
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			routing_entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((routing_entry->hops == 1) && (field_num < MAX_FIELDS_IN_HELLO))
				{
					sprintf (neighbor_name, "NEIGHBOR_%d",field_num);
					op_pk_nfd_set(pkptr , neighbor_name , routing_entry->dest);
					sprintf (bidirect_name, "BIDIRECT_%d",field_num);
					op_pk_nfd_set(pkptr , bidirect_name , routing_entry->bidirect);
					field_num++;
				}
			else if (field_num == MAX_FIELDS_IN_HELLO)
				{
					op_pk_print(pkptr);
					sprintf(msg , "You must increase MAX_FIELDS_IN_HELLO set currently at %d (node %d)" , MAX_FIELDS_IN_HELLO , my_address);
					op_sim_end("You don't have enough fields in the hello packets",msg,"","");
				}
		}
	
	
	//"Delete" useless Neighbor-Fields
	sprintf (neighbor_name , "NEIGHBOR_%d" , field_num);
	sprintf (bidirect_name , "BIDIRECT_%d" , field_num);
	for (i=field_num ;  (i<MAX_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,neighbor_name))  ; i++)
		{
			op_pk_nfd_strip(pkptr , neighbor_name);
			op_pk_nfd_strip(pkptr , bidirect_name);
			sprintf (neighbor_name , "NEIGHBOR_%d" , i+1);
			sprintf (bidirect_name , "BIDIRECT_%d" , i+1);
		}

//FOR GATEWAYS
	//Update the list of Cluster Neighbors
	update_cluster_gw();
	
	//Adds the Cluster-Neighbors
	field_num = 0;
	if ((op_prg_list_size(cluster_gw) != 0) && (my_cluster.clusterhead != my_address))
		for(i=0; i < op_prg_list_size(cluster_gw) ; i++)
			{
				//Gets the address of the cluster
				cl_entry = (struct_cluster_gw*) op_prg_list_access (cluster_gw , i);
			
				//Sets the field
				sprintf(cluster_name, "CLUSTER_%d", field_num++);
				if (field_num <= MAX_CLUSTER_FIELDS_IN_HELLO)
					op_pk_nfd_set(pkptr, cluster_name , cl_entry->cluster);
				else
					{
						sprintf(msg,"You must increase MAX_CLUSTER_FIELDS_IN_HELLO set currently at %d",MAX_CLUSTER_FIELDS_IN_HELLO);
						op_sim_end("An error occured when we generate a hello packet",msg,"","");
					}
			}
	
	//"Delete" useless Cluster-Fields
	sprintf (cluster_name, "CLUSTER_%d",field_num);
	for (i=field_num ;  (i<MAX_CLUSTER_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,cluster_name))  ; i++)
		{
			op_pk_nfd_strip(pkptr , cluster_name);
			sprintf (cluster_name, "CLUSTER_%d",i+1);
		}
	
//TRANSMISSION
	/* Send the packet */
	pk_send_delayed(pkptr , op_dist_uniform(0.05) );
	add_address_id_couple(my_address , current_id-1);
	
	//Next Hello
	if (my_cluster.clusterhead == my_address)
		op_intrpt_schedule_call (op_sim_time() + INTERVALL_HELLO_CH + op_dist_uniform(0.05) , HELLO_GENERATE_CODE , hello , 1);
	else
		op_intrpt_schedule_call (op_sim_time() + INTERVALL_HELLO + op_dist_uniform(0.05) , HELLO_GENERATE_CODE , hello , 1);
}


void update_neighbors (Packet* pkptr) {
	//Control
	int 			addr_temp;	
	char			msg[500];
	//Info abbout source
	int				src_temp , pk_id_temp;
	Boolean			is_link_bidirect;	
	//Cluster
	int				weight_temp , clusterhead_temp;	
	int				cluster_neigh_temp;
	//For list of neighbors in packet
	short			field_num;
	char			field_name[200];
	List*			list_neighbors;
		
//COMMON	
	//Get Infos
	op_pk_nfd_get(pkptr,"SRC",			&src_temp);
	op_pk_nfd_get(pkptr,"PK_ID",		&pk_id_temp);
	op_pk_nfd_get(pkptr,"WEIGHT",		&weight_temp);
	op_pk_nfd_get(pkptr,"CLUSTERHEAD",	&clusterhead_temp);
	
//BIDRECT LINKS DETECTION	
	//Bidirection Detection
	is_link_bidirect = OPC_FALSE;
	field_num = 0; 
	addr_temp = 0;
	sprintf(field_name , "NEIGHBOR_%d", field_num);
	while ((field_num < MAX_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name)) && (!is_link_bidirect) && (addr_temp!=-1))
		{
			op_pk_nfd_get(pkptr , field_name , &addr_temp);
			if (addr_temp == my_address)
				is_link_bidirect = OPC_TRUE;
			sprintf(field_name , "NEIGHBOR_%d", ++field_num);
		}
	
	if (DEBUG>5) 
		{
			sprintf(msg,"I receive an hello from %d (id=%d) at %f -> timeout=%f , bidirect=%d \n",src_temp , pk_id_temp , op_sim_time() , op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO , is_link_bidirect);
			cbrp_debug (msg);
		}	
	
//List of its neighbors
	list_neighbors = create_list_of_neighbors_from_hello_packet(pkptr);
	
	
//ROUTING TABLE	
	//Update The Routing Table
	if (clusterhead_temp != src_temp)
		add_routing_entry (src_temp , src_temp , 1 , weight_temp , clusterhead_temp , INTERVALL_HELLO * TIMEOUT_HELLO , is_link_bidirect , list_neighbors , NULL);
	else
		add_routing_entry (src_temp , src_temp , 1 , weight_temp , clusterhead_temp , INTERVALL_HELLO_CH * TIMEOUT_HELLO_CH , is_link_bidirect , list_neighbors , NULL);

//FOR CLUSTERHEADS -> LIST OF GATEWAYS & CLUSTER-NEIGHBORS	
	//Update List of Cluster-Neighbors (for clusterhead)
	if ((my_address == my_cluster.clusterhead) && (clusterhead_temp == my_address) && (is_link_bidirect))
		{
			//We delete all ols associated cluster associated to this gw (we take care only of the new declared clusters to have the newest information)
			delete_specific_gw_in_cluster_neighbor_gw(src_temp);
			
			//We add the new associated clusters
			sprintf(field_name , "CLUSTER_0");
			for (field_num =0 ; (field_num < MAX_CLUSTER_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr,field_name)) ; field_num++)
				{
					//Manages the declared cluster 
					op_pk_nfd_get (pkptr, field_name, &cluster_neigh_temp);

					add_cluster_neighbor_gw(src_temp , cluster_neigh_temp);
						
					//Next declared Cluster
					sprintf(field_name , "CLUSTER_%d", field_num);
				}
		
		}
}

//Returns the number of 1-Neighbors
int	count_nb_neighbors(){
	struct_routing*		entry;	
	int					degree=0;
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(0);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if (entry->hops == 1)
				degree++;
		}

	//Returns the value
	return(degree);
}

//Return true if I have the highest weight in my 1-Neighborhood of nodes without clusterhead (if it exists some conflict, I break them with identifiers)
Boolean is_highest_node(){
	struct_routing*	entry;	
	int				i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(OPC_TRUE);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((entry->clusterhead == -1) && ((entry->weight > my_cluster.my_weight) || ((entry->weight == my_cluster.my_weight) && (entry->dest < my_address))))
				return (OPC_FALSE);
		}

	//Returns the value
	return(OPC_TRUE);
}




//Return the list of neighbors associated to a node (in routing table)
List* get_list_neighbors_associated(int address){
	int				i ;
	struct_routing*	entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (NULL);
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We found the node !
			if (entry->dest == address)
				return (entry->neighbors);
		}
	
	//No corresponding entry was found
	return(NULL);

}

//Create a List with all bidirect neighbors from a packet hello
List* create_list_of_neighbors_from_hello_packet(Packet* pkptr){
	//Control
	List*	list_neighbors;
	char	neighbor_name[20];
	char	bidirect_name[20];
	int		i;
	//Packet fields
	int		neighbor, bidirect;

	//List Initialization
	list_neighbors	= op_prg_list_create();
	list_neighbors 	= op_prg_mem_alloc (sizeof(List));

	//Get the list of neighbors
	sprintf(neighbor_name,"NEIGHBOR_0");
	sprintf(bidirect_name,"BIDIRECT_0");
	i=0;
	while((i<MAX_FIELDS_IN_HELLO) && (op_pk_nfd_is_set(pkptr, neighbor_name)))
		{
			op_pk_nfd_get(pkptr , neighbor_name , &neighbor);
			op_pk_nfd_get(pkptr , bidirect_name , &bidirect);
			if (bidirect)
				add_integer_in_list(list_neighbors, neighbor);
			i++;
			sprintf(neighbor_name,"NEIGHBOR_%d",i);
			sprintf(bidirect_name,"BIDIRECT_%d",i);
		}
	
	//End
	return(list_neighbors);
			
}



int is_bidirect_neighbor(int address){
	struct_routing*	entry;	
	int				i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(OPC_FALSE);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((entry->dest == address) && (entry->hops == 1) && (entry->bidirect))
				return (OPC_TRUE);
		}

	//Returns the default value
	return(OPC_FALSE);
}










//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		   TOPOLOGY REPRESENTATION (FIGURE GENERATION)
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns a text-formatted number with non significative zeros (i.e. 2 becomes 002)
void format_int_to_string(double src, char* dest, int nb_digits){
	int i;

	//We initialize dest 
	sprintf(dest,"");
	
	//We add non significative zeros (nb digits of src : round( log10(src)+1) ) 
	for(i=0 ; i < nb_digits - ((int)log10(src)+1) ;i++)
		{
			sprintf(dest,"%s%d",dest,0);
		}
	
	//We add the original string 
	sprintf(dest , "%s%f" , dest , src);	
}

//Reinitializes some stats for further writes a new figure
void stats_variable_reinitialization(){
	int 	i , j;

	//NB nodes written
	stats_nb_position_written = 0;		
		
	//Links
	for(i=0 ; i < MAX_NB_NODES ; i++)
		{
			for(j=0 ; j < MAX_NB_NODES ; j++)
				stats_links[i][j] = 0;
		}
}

//Writes figures containing the current topology
void write_topology_figures(int useless_arg , int code){
	FILE*				pfile;
	char				msg[500];
	short				color , radius;
	double				x , y , x_max , y_max;		//Positions in Opnet  (floats)
	int					x1 , x2 , y1 , y2 ;			//Positions in figure (integers)
	int					i , j;
	struct_routing*		entry;
	char				filename [60];
	

	//Next Interruption
	op_intrpt_schedule_call(op_sim_time() + 10.0 , WRITE_TOPOLOGY_CODE , write_topology_figures , 1);
	
	
	//---------------------------------------
	//			GPS Position
	//---------------------------------------	
	if (my_stat_id < MAX_NB_NODES)
		{
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"x position",&x);
			op_ima_obj_attr_get(op_topo_parent (op_id_self()),"y position",&y);
			stats_positions	[my_stat_id][0]	= x;
			stats_positions	[my_stat_id][1]	= y;
	   	}
	else
		{
			sprintf(msg,"You must increase MAX_NB_NODES (%d), my_address (%d) is too high\n",MAX_NB_NODES,my_address);
			printf(msg);
			op_sim_end(msg,"","","");
		}
	
	//Nb of nodes which already wrote their position and stats
	stats_nb_position_written++;

	//---------------------------------------
	//			    Links
	//---------------------------------------	
	if (op_prg_list_size(routing_table)!=0)
		{
			for (i=0; i < op_prg_list_size(routing_table) ; i++)
				{
					//Links
					entry = (struct_routing*) op_prg_list_access(routing_table , i);
					if (entry->hops == 1)				
						stats_links[my_stat_id][address_to_stat_id[entry->relay]] = THICKNESS_PHYSIC_NEIGHBOR;
				}
		}

	//---------------------------------------
	//			    Clusters
	//---------------------------------------	
	stats_cluster [my_stat_id].my_clusterhead = my_cluster.clusterhead;
	
	
	//---------------------------------------
	//			Writes Figures
	//---------------------------------------	
		
	//Writes stats if I'm the last node
	if (stats_nb_position_written == nb_nodes)
		{
	
		//---------------------------------------
		//			cbrp Topology
		//---------------------------------------	
		
			//Opens the associated file and 
			format_int_to_string( op_sim_time() , msg , 4);
			sprintf(filename,"results_cbrp/%d_cbrp_topology_%s.fig" , begin_time , msg);
			
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "X_MAX" , &x_max);
			op_ima_sim_attr_get(OPC_IMA_DOUBLE , "Y_MAX" , &y_max); 
			pfile = fopen(filename,"w");
			if (pfile==NULL)
				{
					printf("Error : we cannot create the file %s\n",filename);
				}
		
			//--------
			//Headers
			//--------
			fprintf(pfile,"#FIG 3.2 \n#Snapshot of The Network Topology for cbrp \nLandscape \nCenter \nInches \nA4 \n100.00 \nSingle \n-2 \n1200 2 \n");						
			fprintf(pfile,"1 3 0 1 0 0 50 -1 15 0.000 1 0.000 0 0 1 1 0 0 0 0\n");
			
			//---------------
			//Nodes Position
			//---------------
			fprintf(pfile,"#NODE POSITIONS AND ADDRESSES\n");
			for(i=0;i<nb_nodes;i++)
				{	
					//Circle to represent the node
					color = stats_cluster[i].my_clusterhead;
					if (stat_id_to_address[i] == stats_cluster[i].my_clusterhead)
						radius = 200;
					else
						radius = 100;
					sprintf(msg,"1 3 0 1 0 %d 50 -1 15 0.000 1 0.000 %d %d %d %d 0 0 0 0\n", color , (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)) , (int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX)) , radius , radius);
					fprintf(pfile,msg);
					
					//Address associated to this node
					sprintf(msg,"4 0 0 50 -1 0 15 0.0000 4 135 135 %d %d %d\\001\n",80+(int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX)),-20+(int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX)),stat_id_to_address[i]);
					fprintf(pfile,msg);
				}
			
			//------
			//Links
			//------
			fprintf(pfile,"#LINKS\n");
			for(i=0;i<nb_nodes;i++)
				{
					for(j=0;j<nb_nodes;j++)
						{
							if (stats_links[i][j]!=0)
								{
									//Coordinates of the source and destination of link
									x1 = (int)(stats_positions[i][0]/(x_max/GRAPHIC_XMAX));
									y1 = (int)(stats_positions[i][1]/(x_max/GRAPHIC_XMAX));
									
									x2 = (int)(stats_positions[j][0]/(x_max/GRAPHIC_XMAX));
									y2 = (int)(stats_positions[j][1]/(x_max/GRAPHIC_XMAX));
									
									color = 10;
									sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 0 0 2\n			%d %d %d %d\n			0.000 0.000\n",stats_links[i][j],x1,y1,x2,y2);
									//With an arrow
									//sprintf(msg,"3 0 0 %d 0 7 50 -1 -1 0.000 0 1 0 2\n			1 1 %f 120.00 240.00\n			%d %d %d %d\n			0.000 0.000\n",stats_links[i][j],(double)stats_links[i][j]/2,x1,y1,x2,y2);
									fprintf(pfile,msg);
								}								
						}
				}
			
			//--------
			//Footers
			//--------
			fclose(pfile);
			
			
			
		//---------------------------------------
		//			END
		//---------------------------------------	
		
			stats_variable_reinitialization();
		}
	}	
	






//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								 COMMON  FUNCTIONS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//Returns 1 if the entry is present in the list, else 0
Boolean is_integer_present_in_list(List* list, int value){
	int		i;
	int*	entry;
	
	//empty list
	if (op_prg_list_size(list) == 0)
		return (OPC_FALSE);
	
	//For each entry of the list
	for (i=0; i < op_prg_list_size(list); i++)
		{
			entry = (int*) op_prg_list_access (list, i);
			if (*entry == value)
				return (OPC_TRUE);
		}
	
	//Default Value
	return (OPC_FALSE);
}

//Adds the entry in the list -> don't verify if the entry exists, already done
Boolean add_integer_in_list(List* list, int value){
	int*	entry;
	
	//Memory allocation
	entry = (int*) malloc (sizeof(int));
			
	//Info
	*entry	= value;
	
	//I add it in the list
	op_prg_list_insert(list, entry , OPC_LISTPOS_TAIL);	
	
}








//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								PACKETS COMMON
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns 1 if the packet comes from a bidirectional link
Boolean is_link_bidirect (int address){
	struct_routing	*entry;
	int				i;
	
	//No declared Neighbor
	if (op_prg_list_size(routing_table)==0)
		return (OPC_FALSE);
	
	//For each entry of the routing table
	for (i=0; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			if ((entry->dest == address) && (entry->hops==1) && (entry->bidirect))
				return (OPC_TRUE);
		}
	
	//Not Found
	return (OPC_FALSE);
}

//Deletes all entries that are timeouted
void delete_timeout_in_addr_pk_id_list(){
	int					i = 0;
	struct_addr_pk_id*	entry;
	char				msg[500];
	
	//If the list is empty
	if (op_prg_list_size(addr_pk_id_list)==0)
		return;
	
	//Search if the entry already exists
	while (i< op_prg_list_size(addr_pk_id_list))
		{
			entry = (struct_addr_pk_id*) op_prg_list_access (addr_pk_id_list, i);
			
			//We delete the entry
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ID-TABLE : deletes the address %d with pk_id %d with timeout %f at %f\n", entry->address , entry->pk_id , entry->timeout , op_sim_time());
							cbrp_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( addr_pk_id_list , i);
					free(entry);
				}
			else
				i++;
		}
}

//=1 if that packet was already seen, 0 else
Boolean addr_pk_id_not_seen (int addr , int pk_id) {
	int					i=0;
	struct_addr_pk_id*	couple;
	
	//For each entry of the list ...
	for(i=0; i< op_prg_list_size(addr_pk_id_list);i++)
		{  
			couple = (struct_addr_pk_id*) op_prg_list_access(addr_pk_id_list,i);
			//.....compare it
			if ((couple->address == addr) && (couple->pk_id == pk_id))
				return(OPC_FALSE);
		}
	return (OPC_TRUE);
}

//Adds this packet as already seen
void add_address_id_couple(int addr , int pk_id){
	struct_addr_pk_id*		couple;
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (struct_addr_pk_id*) malloc ( sizeof (struct_addr_pk_id));
	
	//Info
	couple->address 	= addr;
	couple->pk_id		= pk_id;
	couple->timeout		= op_sim_time() + TIMEOUT_ADDR_PK_ID;
	
	//Insert it
	op_prg_list_insert( addr_pk_id_list, couple, OPC_LISTPOS_TAIL);	
}


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows(Packet* pkptr){
	char	msg[500];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
		
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case UNICAST_ACK_PK_TYPE :
				type = UNICAST_ACK;
			break;
			case HELLO_PK_TYPE :
				type = HELLO;
			break;
			case DATA_PK_TYPE :
				type = DATA;
			break;
			case RREQ_PK_TYPE :
				type = RREQ;
				stats_nb_pk_for_all_rreq++;
			break;
			case RREP_PK_TYPE :
				type = RREP;
			break;
			case RERR_PK_TYPE :
				type = RERR;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case UNICAST_ACK :
				nb_pk_unicast_ack_instantaneous++;
				nb_pk_unicast_ack_total++;
			break;
			case HELLO :
				nb_pk_hello_instantaneous++;
				nb_pk_hello_total++;
			break;
			case DATA :
				nb_pk_data_instantaneous++;
				nb_pk_data_total++;
			break;
			case RREQ :
				nb_pk_rreq_instantaneous++;
				nb_pk_rreq_total++;
			break;
			case RREP :
				nb_pk_rrep_instantaneous++;
				nb_pk_rrep_total++;
			break;
			case RERR :
				nb_pk_rerr_instantaneous++;
				nb_pk_rerr_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void stats_about_control_pk_flows_retransmission(Packet* pkptr){
	char	msg[500];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Gets the type associated to the option_type
	switch (option_type)
		{
			case DATA_PK_TYPE :
				type = DATA;
			break;
			case RREP_PK_TYPE :
				type = RREP;
			break;
			case RERR_PK_TYPE :
				type = RERR;
			break;
			default :
				sprintf(msg,"But we don't find the Packet Option Type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
	
	//Update Stats
	switch(type)
		{
			case DATA :
				nb_pk_data_retransmission_instantaneous++;
				nb_pk_data_retransmission_total++;
			break;
			case RREP :
				nb_pk_rrep_retransmission_instantaneous++;
				nb_pk_rrep_retransmission_total++;
			break;
			case RERR :
				nb_pk_rerr_retransmission_instantaneous++;
				nb_pk_rerr_retransmission_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Add a new Ici in the ici_list
Ici* add_in_ici_list(){
	struct_ici*		entry;
	
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_ici*) malloc ( sizeof (struct_ici));
	
	//Info
	entry->ici_ptr		= op_ici_create("mac_dest_indication");
	entry->timeout		= op_sim_time() + TIMEOUT_ICI ;
	
	//Insert it
	op_prg_list_insert( ici_list , entry , OPC_LISTPOS_TAIL);	
	
	//Return the Ici
	return(entry->ici_ptr);
}

//Delete timeouted entries
void delete_timeout_in_ici_list(){
	int				i = 0;
	struct_ici*		entry;
	
	//If the list is empty
	if (op_prg_list_size(ici_list)==0)
		return;
	
	//For each entry
	for (i = op_prg_list_size(ici_list)-1 ; i>=0 ; i--)
		{
			entry = (struct_ici*) op_prg_list_access (ici_list, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{
					op_prg_list_remove ( ici_list , i);
					free(entry);
				}
		}
	}

//Sends the packet with the specified delay
void pk_send_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	Ici*	ici_ptr;
	char	msg[500];
	
	//Stats
	stats_about_control_pk_flows(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", 			&address_dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE", 	&pk_type);
	
	//Transmission
	if (PROMISCUOUS_FOR_UNICAST)
		address_dest = -1;
	
	//ici	
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr",address_dest);
	
	if (pk_type == DATA_PK_TYPE)
		{
			sprintf(msg, "%d -> %d (%f) (%d)\n", my_address, address_dest , op_sim_time() + delay , is_bidirect_neighbor(address_dest));
			cbrp_test(msg);
		}
	
	//Sends the packet
	op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);
}

//Sends the packet without delay
void pk_send (Packet* pkptr){
	pk_send_delayed(pkptr , 0);
}


//Retransmits the packet with the specified delay
void pk_retransmit_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	Ici*	ici_ptr;
	
	//Stats
	stats_about_control_pk_flows_retransmission(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", &address_dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &pk_type);
	
	//Transmission
	if (PROMISCUOUS_FOR_UNICAST)
		address_dest = -1;
	
	//Ici management
	ici_ptr = add_in_ici_list();
	op_ici_install(ici_ptr);
	op_ici_attr_set(ici_ptr,"dest_addr",address_dest);

	//Transmission
	op_pk_send_delayed(pkptr , STRM_TO_WLAN , delay);
}

//Retransmits the packet without delay
void pk_retransmit (Packet* pkptr){
	pk_retransmit_delayed(pkptr , 0);
}




















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								Acknowledgements
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//This packet must be further acknowledged
void add_unicast_ack(int dest , int pk_id , Packet* pkptr){
	struct_ack*		couple;
	
	//If the list is empty, we must schedule the must verification of timeouts in ack_table (else it is already scheduled)
	if (op_prg_list_size (ack_table) == 0)
		op_intrpt_schedule_self (op_sim_time() + TIMEOUT_UNICAST_ACK , UNICAST_RETRANSMISSIONS_CODE);
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (struct_ack*) malloc ( sizeof (struct_ack));
	
	//Info
	couple->dest		= dest;
	couple->pk_id		= pk_id;
	couple->nb_retry	= 0;
	couple->nb_repairs	= 0;
	couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK ;
	couple->pkptr		= op_pk_copy(pkptr);
	
	//Insert it
	op_prg_list_insert( ack_table , couple , OPC_LISTPOS_TAIL);	
}

//This packet has been acknowledged
void delete_unicast_ack(int dest , int pk_id){
	struct_ack*		couple;
	char			msg[500];
	int				i;
	//Info from packet for debug purpose
	int				pk_type;
	
	//If the list is empty -> I exit !
	if (op_prg_list_size(ack_table)==0)
		{
			if (DEBUG>1)
				{
					sprintf(msg, "ACKS : the entry corresponding to the pk_id %d to destination %d was not found at %f\n",pk_id, dest , op_sim_time());
					cbrp_debug (msg);
				}
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			couple = (struct_ack*) op_prg_list_access (ack_table, i);
			
			if ((couple->dest == dest) && (couple->pk_id==pk_id))
				{
					if (DEBUG>1)
						{
							op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
							sprintf(msg, "ACKS : %d acked the packet with pk_id %d at %f\n", dest , pk_id , op_sim_time());							
							switch (pk_type)
								{
									case DATA_PK_TYPE:
										cbrp_data(msg);
									break;
									case RREP_PK_TYPE :
										cbrp_rrep(msg);
									break;
								}
							cbrp_debug (msg);
						}
					op_prg_list_remove(ack_table, i);
					free(couple);
					return;
				}
		}
	
	if (DEBUG>1)
		{
			sprintf(msg, "ACKS : the entry corresponding to the pk_id %d to destination %d was not found at %f\n",pk_id, dest , op_sim_time());
			cbrp_debug (msg);
		}	
}

//Sends an unicast ack
void acknowledges_unicast_packet(int address , int pk_id){
	char		msg[500];
	Packet*		pkptr;
	int			pk_type;
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("cbrp_pk_unicast_ack");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			address);
	op_pk_nfd_set (pkptr, "TTL" ,			1);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	UNICAST_ACK_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			pk_id);

	if (DEBUG>1)
		{
			sprintf(msg,"ACKS : we send an active ack to %d (for pk-id %d) at %f\n", address , pk_id , op_sim_time());
			op_pk_nfd_get(pkptr, "PK_TYPE",&pk_type);
			switch (pk_type)
				{
					case DATA_PK_TYPE:
						cbrp_data(msg);
						break;
					case RREP_PK_TYPE :
						cbrp_data(msg);
						break;
				}
			cbrp_debug(msg);
		}

	//Sends it
	pk_send_delayed(pkptr, op_dist_uniform(0.001));
}























//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTING
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns the address of a relay toward addr (else -1)
int get_new_relay_toward(int addr){
	int					i , j ;
	struct_routing		*routing_entry;
	int					*neighbor_entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search the entry
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			routing_entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We must observe the list of neighbors associated to this node
			if ((routing_entry->hops == 1) && (routing_entry->bidirect))
				{
					for (j=0 ; j < op_prg_list_size(routing_entry->neighbors); j++)
						{
							//gets the entry
							neighbor_entry = (int*) op_prg_list_access (routing_entry->neighbors, j);

							if (*neighbor_entry == addr)
								return(routing_entry->dest);					
						}
				}					
		}
	
	//No node that corresponds
	return(-1);
}


//Returns the number of hellos missed for a specific node
double get_nb_hellos_missed(int addr){
	double	nb_missed;

	//Different Timeouts for Clusterhead and For Clients
	if (addr == stats_cluster[address_to_stat_id[addr]].my_clusterhead)
		nb_missed = (INTERVALL_HELLO_CH * TIMEOUT_HELLO_CH + op_sim_time() - timeout_routing_entry(addr))/(INTERVALL_HELLO_CH);
	else
		nb_missed = (INTERVALL_HELLO * TIMEOUT_HELLO + op_sim_time() - timeout_routing_entry(addr))/(INTERVALL_HELLO);
	if (nb_missed >0)
		return(nb_missed);
	//The node perhaps changed its status (clusterhead/client), and the timeout was not updated
	else
		return(0);
}

//Returns the structure containing all infos toward the destination (hops, route, relay...)
struct_routing* get_routing_entry(int dest){
	int				i ;
	struct_routing*	entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (NULL);
	
	//Search the entry
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if ((entry->dest == dest) && (entry->bidirect))
				return (entry);
		}
	
	//No corresponding entry was found
	return(NULL);
}


//Returns the timeout time associated to one entry (-1 if no entry was found)
double timeout_routing_entry (int address){
	int				i ;
	struct_routing*	entry;
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if (entry->dest == address)
				return (entry->timeout);
		}
	
	//No corresponding entry was found
	return(-1);
}


//Returns the hops associated to an entry (-1 if no entry was found)
int hops_routing_entry(int address){
	struct_routing*		entry;	
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(-1);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((entry->dest == address) && (entry->bidirect))
				return (entry->hops);
		}

	//Returns the value
	return(-1);
}

//Returns the number of bidirectionnal entries in the routing table
int	count_nb_bidirect_entries_in_routing_table(){
	struct_routing*		entry;	
	int					nb	= 0;
	int					i;
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(0);
	
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if (entry->bidirect)
				nb++;
		}

	//Returns the value
	return(nb);	
}


//Delete the route associated to address
void delete_route(int address){
	int				i = 0;
	struct_routing*	entry;
	char			msg[500];
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(routing_table))
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We delete the entry (which is timeouted)
			if (entry->dest == address)
				{				
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ROUTING-TABLE : deletes the relay %d toward %d (hops=%d), with timeout %f at %f\n", entry->relay , entry->dest , entry->hops , entry->timeout , op_sim_time());
							cbrp_debug(msg);
						}

					if (entry ->hops==1)
						{
							stats_nb_neighbors_changes++;
							op_prg_list_free(entry->route);
						}
					//deletes the corresponding entry
					else
						{
							op_prg_list_remove ( routing_table , i);
							free(entry);
						}

					
					return;
				}
			i++;
		}

}

//Delete all entries in routing table that overcome the timeout
void delete_timeout_in_routing_table (){
	int				i = 0;
	struct_routing*	entry;
	char			msg[500];
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(routing_table))
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{				
					//Stats
					if (entry ->hops==1)
						stats_nb_neighbors_changes++;

					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ROUTING-TABLE : deletes the relay %d toward %d (hops=%d), with timeout %f at %f\n", entry->relay , entry->dest , entry->hops , entry->timeout , op_sim_time());
							cbrp_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( routing_table , i);
					free(entry);
				}
			else
				i++;
		}
}


//Adds an entry in the routing table :
// ->If one exists and is farther, we update with the new information
// ->If none exists, we add it
void add_routing_entry (int dest, int relay , short hops , int weight , int clusterhead , double timeout , Boolean bidirect , List* list_neighbors , List* route){	int				i = 0;
	struct_routing*	entry;
	char			msg[500];
	Boolean			chgt;
	
	//Search if the entry already exists
	while ((op_prg_list_size(routing_table)!=0) && (i< op_prg_list_size(routing_table) ))
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			//We update the entry (which is nearer)
			if ((entry->dest == dest) && (entry->hops >= hops))
				{
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"ROUTING-TABLE : updates the relay %d toward %d (hops=%d), at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
							cbrp_debug(msg);
						}				
					
					//Stats
					chgt = (hops == 1) && (hops != entry->hops);
					chgt = chgt || ((entry->hops == 1) && (hops != entry->hops));
					chgt = chgt || (entry->bidirect != bidirect);
					if (chgt)	
						stats_nb_neighbors_changes++;
					
					//Updates info
					entry->relay		= relay;
					entry->hops			= hops;	
					entry->weight		= weight;
					entry->clusterhead	= clusterhead;
					entry->timeout 		= op_sim_time() + timeout;				
					entry->bidirect		= bidirect;
					entry->neighbors	= list_neighbors;
					entry->route		= route;

					//That's all
					return;
				}
			
			//The entry is not acceptable -> too far
			if ((entry->dest == dest) && (entry->hops < hops))
				return;
			i++;
		}
	
	//The entry was not found
	//Memory allocation
	entry = (struct_routing*) malloc (sizeof(struct_routing));
			
	//Info
	entry->dest			= dest;
	entry->relay		= relay;
	entry->weight		= weight;
	entry->clusterhead	= clusterhead;
	entry->hops			= hops;
	entry->bidirect 	= bidirect;
	entry->timeout 		= op_sim_time() + timeout;
	entry->neighbors	= list_neighbors;
	entry->route		= route;
	
	//Stats
	stats_nb_neighbors_changes++;
	
	//DEBUG
	if (DEBUG>5)
		{
			sprintf(msg,"ROUTING-TABLE : adds the relay %d toward %d (hops=%d), at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
			cbrp_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert( routing_table, entry, OPC_LISTPOS_TAIL);	
}

//Looks for the relay toward a destination (returns -1 if none was found)
int get_relay_in_routing_table(int dest){
	int				i = 0;
	struct_routing*	entry;
	char			msg[500];
	
	if (op_prg_list_size(routing_table)==0)
		return (-1);
	
	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
			if ((entry!=NULL) && (entry->dest == dest) && (entry->bidirect))				
				{
					//DEBUG
					if (DEBUG>4)
						{
							sprintf(msg,"ROUTING : I find the relay %d toward %d (%d hops far) at %f\n", entry->relay , entry->dest , entry->hops , op_sim_time());
							cbrp_debug(msg);
						}

					return (entry->relay);
				}
	}
		
	//DEBUG
	if (DEBUG>1)
		{
			sprintf(msg,"ROUTING : I didn't find any relay toward %d at %f\n", dest , op_sim_time());
			cbrp_debug(msg);
		}		
		
	//No valid entry found	
	return(-1);
}


















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								CLUSTER
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//I become clusterhead -> Sets some stats, sends decision...
void become_clusterhead(){
	char	msg[500];

	//Set my clusterhead
	my_cluster.clusterhead 			= my_address;
	my_cluster.last_time_usefull	= op_sim_time();
	
	if (DEBUG > 2)
		{
			sprintf(msg, "CLUSTER : I become clusterhead at %f\n",op_sim_time());
			cbrp_debug (msg);
		}
	

	//Sends a gratuitous hello to advertise my decision
	hello(0 , 0);
	
	//Stats
	stats_nb_ch_changes++;
		
	//Stats
	stats_cluster [my_stat_id].my_clusterhead = my_cluster.clusterhead;
}

//Change my clusterhead
void change_clusterhead(int clusterhead){
	char	msg[500];

	//Stats
	if (clusterhead != -1)
		stats_nb_ch_clients_changes++;
	
	//Debug
	if (DEBUG>6)
		{
			sprintf(msg, "CLUSTER : I change my clusterhead from %d to %d at %f\n", my_cluster.clusterhead, clusterhead, op_sim_time());
			cbrp_debug (msg);
		}
	
	//Changes it
	my_cluster.clusterhead = clusterhead;
	
	//Empty List for all cluster neighbors
	delete_all_in_cluster_gw();
	
	//Stats
	stats_cluster [my_stat_id].my_clusterhead = my_cluster.clusterhead;
}


//Search if an entry could be my clusterhead (else return -1)
int search_a_new_clusterhead(){
	struct_routing*		entry;	
	int					i;
	struct_routing*		best_entry;
		
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(-1);
		
	//For each entry
	best_entry = NULL;
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((entry->clusterhead == entry->dest) && (entry->hops==1) && (entry->bidirect) && (entry->timeout >= op_sim_time()) && ((best_entry == NULL) || (entry->weight > best_entry->weight)))
				best_entry = entry;
		}

	//Returns the value
	if (best_entry != NULL)
		return (best_entry->dest);
	else
		return (-1);
}

//Return 1 If no 1-Neighbor chose me as clusterhead
Boolean is_useless_clusterhead(){
	struct_routing*		entry;	
	int					i;
		
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return(OPC_TRUE);
		
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			if ((entry->clusterhead == my_address) && (entry->bidirect) && (entry->hops == 1))
				return (OPC_FALSE);
		}

	//Returns the default value
	return (OPC_TRUE);
}



















//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								CLUSTER GATEWAYS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//////////////////////////////////////////////
/////////////// FOR CLIENTS //////////////////
//////////////////////////////////////////////


//Adds a cluster neighbor of my cluster (declared by another node)
void add_cluster_gw(int addr){
	int					i = 0;
	struct_cluster_gw*	entry;
	char				msg[500];

	//Search if the entry already exists
	if (op_prg_list_size(cluster_gw) !=0 )
		{
			//For each entry
			for (i=0 ; i < op_prg_list_size(cluster_gw) ; i++)
				{
					entry = (struct_cluster_gw*) op_prg_list_access (cluster_gw, i);
			
					//We delete the entry
					if (entry->cluster == addr)
						{
							if (DEBUG>4)
								{
									sprintf(msg , "CLUSTER-GW : updates the cluster-neighbor %d at %f\n", addr , op_sim_time());
									cbrp_debug(msg);
								}

							entry->timeout = op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
							return;
						}
				}
		}
	
	//The entry was not found
	//Memory allocation
	entry = (struct_cluster_gw*) malloc (sizeof(struct_cluster_gw));
			
	//Info
	entry->cluster		= addr;
	entry->timeout		= op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
	//DEBUG
	if (DEBUG>4)
		{
			sprintf(msg , "CLUSTER-GW : adds the cluster-neighbor %d at %f\n", addr , op_sim_time());
			cbrp_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert(cluster_gw, entry, OPC_LISTPOS_TAIL);	
}

//delete all entries in the list of cluster-neighbors (I change my clusterhead...)
void delete_all_in_cluster_gw(){
	int					i = 0;
	struct_cluster_gw*	entry;
	char				msg[500];
	
	//Deletes the timeouted local clusters
	if (op_prg_list_size(cluster_gw) != 0)
		{
			for (i = op_prg_list_size(cluster_gw)-1 ; i >=0 ; i--)
				{
					//deletes the corresponding entry
					entry = op_prg_list_remove (cluster_gw , i);
					
					//DEBUG
					if (DEBUG>4)
						{
							sprintf(msg , "CLUSTER-GW : deletes the cluster-neighbor %d timeout %f at %f\n", entry->cluster , entry->timeout , op_sim_time());
							cbrp_debug(msg);
						}
					
					free(entry);
				}
		}
}

//Update my list of cluster Neighbors according to Neighborhood Table
void update_cluster_gw(){
	struct_routing*		entry;	
	int					i;
	
	//Empty the list of my Cluster-Neighbors
	delete_all_in_cluster_gw();
	
	//Empty Routing Table
	if (op_prg_list_size(routing_table) == 0)
		return;
		
	//For each entry
	for (i=0; i < op_prg_list_size(routing_table) ; i++) 
		{
			entry = (struct_routing*) op_prg_list_access (routing_table , i);
			
			if ((entry->clusterhead != my_cluster.clusterhead) && (entry->bidirect) && (entry->hops==1))
				add_cluster_gw(entry->clusterhead);
		}
}




///////////////////////////////////////////////////
/////////////// FOR CLUSTERHEADS //////////////////
///////////////////////////////////////////////////




//Updates the association between one of my gateways and its cluster 
void add_cluster_neighbor_gw (int gw , int cluster){
	int					i = 0;
	struct_cl_neigh*	entry;
	char				msg[500];

	//Search if the entry already exists
	if (op_prg_list_size(cluster_neighbors) !=0 )
		{
			//For each entry
			for (i=0 ; i < op_prg_list_size(cluster_neighbors) ; i++)
				{
					entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
			
					//We update the entry
					if ((entry->cluster == cluster) && (entry->gw == gw))
						{
							if (DEBUG>4)
								{
									sprintf(msg,"CLUSTER-NEIGH : updates the cluster-neighbor %d via gw %d at %f\n", entry->cluster , entry->gw , op_sim_time());
									cbrp_debug(msg);
								}

							entry->timeout = op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
							return;
						}
				}
		}
	
	//The entry was not found
	//Memory allocation
	entry = (struct_cl_neigh*) malloc (sizeof(struct_cl_neigh));
			
	//Info
	entry->cluster		= cluster;
	entry->gw			= gw;
	entry->timeout		= op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
	
	//DEBUG
	if (DEBUG>4)
		{
			sprintf(msg,"CLUSTER-NEIGH : adds the cluster-neighbor %d via gw %d at %f\n", entry->cluster , entry->gw , op_sim_time());
			cbrp_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert(cluster_neighbors, entry, OPC_LISTPOS_TAIL);	

}

//delte all timeouted entries in the list of cluster for which I am gateway
void delete_timeout_in_cluster_neighbor_gw(){
	int					i = 0;
	struct_cl_neigh*	entry;
	char				msg[500];
	
	//Deletes the timeouted local clusters
	if (op_prg_list_size(cluster_neighbors) != 0)
		{
			for (i = op_prg_list_size(cluster_neighbors)-1 ; i >=0 ; i--)
				{
					entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
					//We update the entry
					if (entry->timeout < op_sim_time())
						{	
							//DEBUG
							if (DEBUG>4)
								{
									sprintf(msg,"CLUSTER-NEIGH : deletes the cluster-neighbor %d via gw %d timeout %f %d at %f\n", entry->cluster , entry->gw , entry->timeout , op_sim_time());
									cbrp_debug(msg);
								}
							
							//deletes the corresponding entry
							op_prg_list_remove (cluster_neighbors , i);
							free(entry);
						}
				}
		}
}

//Empty the list of neighbors of one specific gateway (We received an hello -> we delete old entries)
void delete_specific_gw_in_cluster_neighbor_gw(int addr){
	int					i = 0;
	struct_cl_neigh*	entry;
	
	//Deletes the timeouted local clusters
	if (op_prg_list_size(cluster_neighbors) != 0)
		{
			for (i = op_prg_list_size(cluster_neighbors)-1 ; i >=0 ; i--)
				{
					entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
					//We update the entry
					if (entry->gw == addr)
						{
							op_prg_list_remove (cluster_neighbors , i);
							free(entry);
						}
				}
		}
}













//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								CLUSTER TOPOLOGY
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Returns 1 if the entry is present, else 0
Boolean exists_stats_cluster_local(int addr){
	int		i = 0;
	int*	entry;
	
	//If the list is empty
	if (op_prg_list_size(stats_cluster_local)==0)
		return (OPC_FALSE);
	
	//For each entry, takes its timeout
	for (i=0 ; i < op_prg_list_size(stats_cluster_local) ; i++)
		{
			entry = (int*) op_prg_list_access (stats_cluster_local, i);
			
			//We delete the entry
			if (*entry == addr)
				return(OPC_TRUE);
		}

	//Default Value
	return(OPC_FALSE);
}

//Adds a cluster neighbor of my cluster (declared by another node)
void add_stats_cluster_local(int addr){
	int		i = 0;
	int*	entry;
	char	msg[500];

	//Search if the entry already exists
	if (exists_stats_cluster_local(addr))
		return;
	
	//The entry was not found
	//Memory allocation
	entry = (int*) malloc (sizeof(int));
			
	//Info
	*entry		= addr;
	
	//Stats
	stats_nb_virtual_changes++;
	
	//DEBUG
	if (DEBUG>5)
		{
			sprintf(msg,"CLUSTER-LOCAL : adds the cluster-neighbor %d at %f\n", addr , op_sim_time());
			cbrp_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert( stats_cluster_local, entry, OPC_LISTPOS_TAIL);	
}


//Returns 1 if the entry is present, else 0
Boolean is_stats_local_present_in_stats_global(int addr1){
	int					i = 0;
	struct_stats_cl*	entry;
	int					addr_lower , addr_higher;
	
	//Ordonates
	if (addr1 < my_cluster.clusterhead)
		{
			addr_lower	= addr1;
			addr_higher = my_cluster.clusterhead;
		}
	else
		{
			addr_lower	= my_cluster.clusterhead;
			addr_higher = addr1;
		}
	
	
	//If the list is empty
	if (op_prg_list_size(stats_cluster_global)==0)
		return (OPC_FALSE);
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(stats_cluster_global) ; i++)
		{
			entry = (struct_stats_cl*) op_prg_list_access (stats_cluster_global, i);
			
			if ((entry->addr1 == addr_lower) && (entry->addr2 == addr_higher))
				return(OPC_TRUE);
		}

	//Default Value
	return(OPC_FALSE);
}

//Updates my cluster local according to my cluster globals
void update_stats_cluster_local_list(){
	int					i = 0;
	int*				cl_local;
	struct_stats_cl*	cl_global;
	char				msg[500];
	
//Deletes the timeouted local clusters
	if (op_prg_list_size(stats_cluster_local) != 0)
		{
			while (i< op_prg_list_size(stats_cluster_local))
				{
					cl_local = (int*) op_prg_list_access (stats_cluster_local, i);
					//We delete the entry
					if (!is_stats_local_present_in_stats_global(*cl_local))
						{	
							//DEBUG
							if (DEBUG>5)
								{
									sprintf(msg,"CLUSTER-LOCAL : deletes the cluster-neighbor %d at %f\n", *cl_local , op_sim_time());
									cbrp_debug(msg);
								}
					
							//Stats
							stats_nb_virtual_changes++;
							
							//deletes the corresponding entry
							op_prg_list_remove ( stats_cluster_local , i);
							free(cl_local);
						}
					i++;
				}
		}	

//Adds the new local clusters
	//If the list is empty
	if (op_prg_list_size(stats_cluster_global) != 0)
		{
			for (i=0 ; i < op_prg_list_size(stats_cluster_global) ; i++)
				{
					cl_global = (struct_stats_cl*) op_prg_list_access (stats_cluster_global, i);
			
					//We delete the entry
					if (cl_global->addr1 == my_cluster.clusterhead)
						add_stats_cluster_local(cl_global->addr2);
					if (cl_global->addr2 == my_cluster.clusterhead)						
						add_stats_cluster_local(cl_global->addr1);
				}
		}
	
}


//Dels a cluster neighbor of my cluster (I am not yet gateway -> I update only MY entries)
void delete_timeout_in_stats_cluster_global(){
	int					i = 0;
	struct_stats_cl*	entry;
	char				msg[500];
	
	//If the list is empty
	if (op_prg_list_size(stats_cluster_global)==0)
		return;
	
	//For each entry, takes its timeout
	while (i< op_prg_list_size(stats_cluster_global))
		{
			entry = (struct_stats_cl*) op_prg_list_access (stats_cluster_global, i);
			
			//We delete the entry
			if ((entry->timeout < op_sim_time()) && (entry->src == my_address))
				{				
					//DEBUG
					if (DEBUG>5)
						{
							sprintf(msg,"CLUSTER-GLOBAL : deletes the cluster adjacency %d/%d, with timeout %f at %f (position %d)\n", entry->addr1 , entry->addr2 , entry->timeout , op_sim_time() , i);
							cbrp_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove (stats_cluster_global , i);
					free(entry);
				}
			else
				i++;
		}
}


//Adds a cluster neighbor of my cluster (I am gateway)
void add_stats_cluster_global(int addr1, int addr2){
	int					i = 0;
	struct_stats_cl*	entry;
	int					addr_lower , addr_higher;
	char				msg[500];
	
	//Ordonates
	if (addr1 < addr2)
		{
			addr_lower	= addr1;
			addr_higher = addr2;
		}
	else
		{
			addr_lower	= addr2;
			addr_higher = addr1;
		}
	
	//Search if the entry already exists
	while ((op_prg_list_size(stats_cluster_global)!=0) && (i< op_prg_list_size(stats_cluster_global) ))
		{
			entry = (struct_stats_cl*) op_prg_list_access (stats_cluster_global, i);
			
			//If the entry exists -> Nothing to do
			if ((entry->addr1 == addr_lower) && (entry->addr2 == addr_higher)) //We don't care to have the corresponding source, we just want to have the cluster topology && (entry->src == my_address))
				{		
						//Info
						entry->src 			= my_address;
						entry->timeout		= op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
							
						//DEBUG
						if (DEBUG>5)
							{
								sprintf(msg,"CLUSTER-GLOBAL : updates the cluster adjacency %d/%d at %f\n", addr1 , addr2 , op_sim_time());
								cbrp_debug(msg);
							}

					return;
				}
			i++;
		}
	
	//The entry was not found
	//Memory allocation
	entry = (struct_stats_cl*) malloc (sizeof(struct_stats_cl));
			
	//Info
	entry->addr1		= addr_lower;
	entry->addr2		= addr_higher;
	entry->src 			= my_address;
	entry->timeout		= op_sim_time() + INTERVALL_HELLO * TIMEOUT_HELLO;
	
	//DEBUG
	if (DEBUG>5)
		{
			sprintf(msg,"CLUSTER-GLOBAL : adds the cluster adjacency %d/%d at %f\n", addr1 , addr2 , op_sim_time());
			cbrp_debug(msg);
		}
	
	//I add it in the list
	op_prg_list_insert(stats_cluster_global, entry , OPC_LISTPOS_TAIL);	
}









//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTE REQUEST
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//delete an entry in the rreq pk buffer
int delete_entry_in_rreq_buffer(int address){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	double					older_entry=-1;
	int						value;
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return(-1);

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);			
			//We delete the entry
			if (entry->dest == address)
				{	
					value = entry->nb_retry;
					op_prg_list_remove ( rreq_pk_buffer , i);
					free(entry);
					return (value);
				}
		}
	
	return(-1);
}	

//When the simulation ends
void delete_all_in_rreq_pk_buffer(){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[500];
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return;

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			
			if (DEBUG>2)
				{
					sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
					cbrp_rreq(msg);
				}
			(stats_rreq [entry->stat_id]).rreq_nb_retry =  entry->nb_retry + 1;
			op_prg_list_remove ( rreq_pk_buffer , i);
			free(entry);
		}
}

//Timeout entries in Route Requests pk buffer
void send_timeout_in_rreq_pk_buffer(int useless_arg , int code){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[500];
	double					older_entry=-1;
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return;

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			
			//We delete the entry
			if (entry->timeout <= op_sim_time())
				{	
					//If we send a new RREQ, are we over our quota of RREQ ? 
				   	if (entry->nb_retry + 1 <= MAX_NB_RREQ_RETRY)
						{
							//DEBUG
							if (DEBUG>2)
								{
									sprintf(msg,"RREQ-BUFFER : %d retransmits the rreq toward %d with timeout %f at %f\n", my_address , entry->dest , entry->timeout , op_sim_time());
									cbrp_rreq(msg);
								}
							//Sends a new RREQ
							send_rreq_pk(entry->dest, entry->stat_id);
							
							//Info update
							entry->nb_retry ++;
							
							//We have a bigger timeout in order to have the entry if we receive a RREP with this new retry (anywhere, we won't retransmit the packet)
							//if (entry->nb_retry == MAX_NB_RREQ_RETRY)
							//	entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER*10;
							//else
							//	{
									entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER;
		
									//The older entry
									if ((entry->timeout < older_entry) || (older_entry == -1))						
										older_entry = entry->timeout;
							//	}
							
						}
					//deletes the corresponding entry
					else					
						{
							if (DEBUG>2)
								{
									sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
									cbrp_rreq(msg);
								}
							(stats_rreq	[entry->stat_id]).rreq_nb_retry =  entry->nb_retry + 1;
							op_prg_list_remove ( rreq_pk_buffer , i);
							free(entry);
						}
				}
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;

		}
	
	if (older_entry!=-1)
		{
			op_intrpt_schedule_call(older_entry , RREQ_SEND_TIMEOUT_CODE , send_timeout_in_rreq_pk_buffer , 1);
			sprintf(msg, "older entry is %f\n",older_entry);
			cbrp_debug(msg);
			print_rreq_pk_buffer();
		}
	else
		{
			sprintf(msg, "older entry is %f\n",older_entry);
			cbrp_debug(msg);
			print_rreq_pk_buffer();
		}
		
}

//Is the entry already in the table ?
Boolean entry_exists_in_rreq_pk_buffer (int dest){
	struct_rreq_pk_buffer*	entry;
	int						i;

	//No entry present
	if (op_prg_list_size(rreq_pk_buffer) == 0)
		return (OPC_FALSE);

	//Search if the entry already exists
	for (i=0 ; i<op_prg_list_size(rreq_pk_buffer); i++)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			if (entry->dest == dest)
				return(OPC_TRUE);

		}
	
	//Not found
	return(OPC_FALSE);
}

//Add the data packet in the buffered list
void add_in_rreq_pk_buffer(int dest, int stat_rreq_id){
	struct_rreq_pk_buffer*	entry;

	//The entry doesn't exist
	if (entry_exists_in_rreq_pk_buffer (dest))
		return;
	
	//Next table verification forn retransmissions
	if (op_prg_list_size(rreq_pk_buffer) == 0)
		op_intrpt_schedule_call (op_sim_time() + TIMEOUT_RREQ_PK_BUFFER, RREQ_SEND_TIMEOUT_CODE , , send_timeout_in_rreq_pk_buffer , 1);
	
	//Memory allocation
	entry = (struct_rreq_pk_buffer*) malloc (sizeof(struct_rreq_pk_buffer));
			
	//Info
	entry->dest		= dest;
	entry->timeout	= op_sim_time() + TIMEOUT_RREQ_PK_BUFFER;
	entry->nb_retry	= 0;
	entry->stat_id	= stat_rreq_id;
	
	//I add it in the list
	op_prg_list_insert(rreq_pk_buffer, entry , OPC_LISTPOS_TAIL);	
}


//Returns the address of the relay toward cluster (if the clusterhead is neighbor, returns the clusterhead)
int	get_relay_toward_cluster(int cluster){
	struct_routing*		entry;
	int					i;
	int					relay = -1;

	//Direct Cluster Neighbors
	if (op_prg_list_size(routing_table) == 0)
		return(-1);
	
	for (i=0; i < op_prg_list_size(routing_table); i++)
		{
			entry = (struct_routing*) op_prg_list_access (routing_table, i);
				
			//If the cluster corresponds
			if ((entry->clusterhead == cluster) && (entry->bidirect) && (entry->hops==1))
				relay = entry->dest;
			if ((entry->dest == cluster) && (entry->bidirect) && (entry->hops==1))
				return(cluster);
		}
	
	return(relay);
}

//Adds one node address at the end of set relay fields
void add_in_relay_fields(Packet* pkptr, int address){
	int		field_num = 0;
	char	field_name[200];
	char	msg[500];
	
	for (field_num =0 ; field_num < MAX_RELAY_FIELDS_IN_RREQ_PK ; field_num++)
		{
			sprintf(field_name, "RELAY_%d", field_num);
			if (!op_pk_nfd_is_set(pkptr, field_name))
				{
					op_pk_nfd_set(pkptr, field_name, address);
					return;
				}
		}
	
	//We have not enough relay fields
	sprintf(msg , "We have currently only %d fields",MAX_RELAY_FIELDS_IN_RREQ_PK);
	op_pk_print(pkptr);
	op_sim_end("We have not enough relay Fields in the RREQ Packets", msg ,"","");
}



//Adds my address at the end of set relay fields
void add_me_in_relay_fields(Packet* pkptr){

	add_in_relay_fields(pkptr, my_address);
}

//Complete the packet with the clusters associated to the specified node  (CLUSTER_DEST_i fields)
//The clusters associated to this gateway are searched in the cluster_neighbors list from index_start_list to the end (possible sparing if the remaining part was already handled)
void complete_with_other_clusters_associated_to_this_gw(Packet* pk_dest , int index_start_list , int addr , List* already_sent){
	int					field_num;
	char				field_name[200];
	int					i;
	char				msg[500];
	struct_cl_neigh		*cl_entry;		
	
	//For each cluster associated to this gateway, adds it in the CLUSTER_DEST_%d list
	field_num = 1;
	for (i = index_start_list ; i < op_prg_list_size(cluster_neighbors) ; i++)
		{
			cl_entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
			if ((cl_entry->gw == addr) && (!is_integer_present_in_list(already_sent, cl_entry->cluster)))
				{
					if (field_num < MAX_CLUSTER_FIELDS_IN_RREQ_PK)
						{
							sprintf(field_name, "CLUSTER_DEST_%d", field_num++);
							op_pk_nfd_set(pk_dest , field_name, cl_entry->cluster);
									
							//Adds this node in list of covered nodes
							add_integer_in_list(already_sent, cl_entry->cluster);
							
							//Debug
							if (DEBUG>1)
								{
									sprintf(msg, "RREQ -> 			  and to reach %d (GWS)\n",cl_entry->cluster);
									cbrp_rreq(msg);
								}
						}
					else
						{
							sprintf(msg, "MAX_CLUSTER_FIELDS_IN_RREQ_PK is currently set to %d", MAX_CLUSTER_FIELDS_IN_RREQ_PK);
							op_sim_end("We have not enough place to set all cluster-destination in a RREQ",msg,"You must increase this value in the Header Block of the program","");
						}
				}
		}
	//"Deletes" unused fields
	for (i = field_num ; i <= MAX_CLUSTER_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name, "CLUSTER_DEST_%d", i);	
			if (op_pk_nfd_is_set(pk_dest, field_name))
				op_pk_nfd_strip (pk_dest , field_name);
		}
}

//Sends the RREQ "pk_src" to all my clients (I am a clusterhead)
void send_rreq_pk_to_clients(pk_src){
	char		msg[500];
	Packet*		pk_dest;
	
	if (DEBUG>1)
		{
			sprintf(msg, "%d sends in broadcast the RREQ to all its clients at %f\n",my_address,op_sim_time());
			cbrp_rreq(msg);
		}

	//In Broadcast
	pk_dest =  op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest, "DEST", -1);
	
	//Transmission
	pk_send_delayed(pk_dest , 0.003);		
}


//Sends the packet to all gateways
void set_dest_for_broadcast_pk_for_clusterhead(Packet *pk_src , double delay){
	//To manipulate special structures
	struct_routing		*routing_entry;
	struct_cl_neigh		*cl_entry ;
	//List of Destination already handled
	List				*already_sent;
	//Common
	Packet				*pk_dest;
	int					i ;
	char				msg[500];
	//Fields in Packet
	int					field_num;
	char				field_name[200];
	int					address_relay;
	
	//Initialization
	already_sent	= op_prg_list_create();
	already_sent 	= op_prg_mem_alloc (sizeof(List));
	add_integer_in_list(already_sent, my_cluster.clusterhead);
	add_integer_in_list(already_sent, -1);
	
	//The previous intermediate nodes are added as covered
	field_num = 0;
	sprintf(field_name, "RELAY_%d", field_num);
	while ((field_num < MAX_RELAY_FIELDS_IN_RREQ_PK) && (op_pk_nfd_is_set(pk_src, field_name)))
		{					
			op_pk_nfd_get(pk_src, field_name, &address_relay);
			add_integer_in_list(already_sent, address_relay);
			field_num++;
			sprintf(field_name, "RELAY_%d", field_num);
		}
	
	
	//Direct Cluster Neighbors
	if (op_prg_list_size(routing_table) != 0)
		for (i=0; i < op_prg_list_size(routing_table); i++)
			{
				routing_entry = (struct_routing*) op_prg_list_access (routing_table, i);
				
				//For each different cluster
				if ((routing_entry->clusterhead != -1) && (routing_entry->clusterhead != my_address) && (routing_entry->bidirect) && (routing_entry->hops==1) && (!is_integer_present_in_list(already_sent, routing_entry->clusterhead)))
					{
						//Infos
						pk_dest = op_pk_copy(pk_src);
						op_pk_nfd_set(pk_dest , "DEST", routing_entry->dest);						
						
						//Sets the cluster destination
						op_pk_nfd_set(pk_dest , "CLUSTER_DEST_0", routing_entry->clusterhead);						

						//Marked as already sent
						add_integer_in_list(already_sent, routing_entry->clusterhead);					
						
						if(DEBUG>1)
							{
								sprintf(msg, "RREQ -> from %d to %d to reach %d\n",my_address, routing_entry->dest , routing_entry->clusterhead);
								cbrp_rreq(msg);
							}
						
						//For all clusters associated to this destination
						complete_with_other_clusters_associated_to_this_gw(pk_dest , 0 , routing_entry->dest , already_sent);
						
						//Transmission
						pk_send_delayed(pk_dest,op_dist_uniform(0.001));						
					}
			}
	
	//Gateways
	if (op_prg_list_size(cluster_neighbors) != 0)
		for (i=0; i < op_prg_list_size(cluster_neighbors); i++)
			{
				cl_entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
				
				//For each different cluster
				if (!is_integer_present_in_list(already_sent, cl_entry->cluster))
					{
						//Infos
						pk_dest = op_pk_copy(pk_src);
						op_pk_nfd_set(pk_dest , "DEST", cl_entry->gw);						
						
						//Sets the cluster destination
						op_pk_nfd_set(pk_dest , "CLUSTER_DEST_0", cl_entry->cluster);						
						
						//Marked as already sent
						add_integer_in_list(already_sent, cl_entry->cluster);					
						
						if (DEBUG>1)
							{
								sprintf(msg,"RREQ -> from %d to %d to reach %d (GWS)\n",my_address, cl_entry->gw , cl_entry->cluster);
								cbrp_rreq(msg);
							}

						//For all clusters associated to this gateway
						complete_with_other_clusters_associated_to_this_gw(pk_dest , i+1 , cl_entry->gw , already_sent);
						
						//Transmission	
						pk_send_delayed(pk_dest , op_dist_uniform(0.001));
					}	
			}
	

}

void send_rreq_pk(int final_dest , int stat_rreq_id){
	Packet*		pkptr;
	int			i;
	char		field_name[200];
	char		msg[500];
	
	if (DEBUG>1)
		{
			sprintf(msg, "\n\n !!!!!!!!!!!   %d sends a RREQ to %d at %f !!!!!!!!!!!!!!!!!!! \n \n \n",my_address , final_dest , op_sim_time());
			cbrp_rreq(msg);
		}
	
	//Creation
	pkptr = op_pk_create_fmt("cbrp_rreq");
	
	//Infos
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "SRC_INIT" , 		my_address);
	op_pk_nfd_set(pkptr , "RELAY_0" , 		my_address);
	op_pk_nfd_set(pkptr , "DEST_FINAL" , 	final_dest);
	
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	RREQ_PK_TYPE);
	op_pk_nfd_set(pkptr , "TTL" , 			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pkptr , "PK_ID" , 		current_id++);
	op_pk_nfd_set(pkptr , "STAT_ID" , 		stat_rreq_id);

	//"Deletes" unused fields
	for (i=1; i <= MAX_RELAY_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "RELAY_%d", i);
			op_pk_nfd_strip (pkptr, field_name);
		}
	
	
//UNICAST for gateways	
	//Destination(s)
	if (my_cluster.clusterhead != my_address)
		{
			op_pk_nfd_set(pkptr , "DEST" , my_cluster.clusterhead);
			
			if (DEBUG>1)
				{
					sprintf(msg,"RREQ -> %d is client, it sends its RREQ to its clusterhead %d at %f\n",my_address, my_cluster.clusterhead, op_sim_time());
					cbrp_rreq(msg);
				}
			
			//Transmission
			add_address_id_couple(my_address , current_id-1);
			pk_send_delayed(pkptr , op_dist_uniform(0.001));
		}
	else
		{
			//BROADCAST for clients
			send_rreq_pk_to_clients(pkptr);
			//UNICAST for GATEWAYS	
			set_dest_for_broadcast_pk_for_clusterhead(pkptr, op_dist_uniform(0.001));
			add_address_id_couple(my_address , current_id-1);
		}
}	


//Sends A Route Request
void send_rreq(int final_dest){
	int		i;

	//Is a RREQ already sent ?
	if (!entry_exists_in_rreq_pk_buffer(final_dest))
		{
			//Add this RRREQ in buffer potential Retries, and send a generate a RREQ pk
			add_in_rreq_pk_buffer(final_dest, stats_nb_rreq);
			send_rreq_pk(final_dest, stats_nb_rreq);
	
			//Stats
			(stats_rreq [stats_nb_rreq].rreq_is_rcvd)[my_stat_id] = 1;
			stats_rreq [stats_nb_rreq].source 		= my_address;
			stats_rreq [stats_nb_rreq].dest		 	= final_dest;
	
			//List of current clusterheads
			for (i=0; i < nb_nodes ; i++)
				{
					if (stats_cluster [i].my_clusterhead == stat_id_to_address [i])
						(stats_rreq [stats_nb_rreq].rreq_is_ch)[i] = 1;
					else
						(stats_rreq [stats_nb_rreq].rreq_is_ch)[i] = 0;
				}
	
			//Stats & Control for Pk_id
			(stats_rreq	[stats_nb_rreq]).rreq_time_emission	= op_sim_time();
	
			if (stats_nb_rreq > MAX_RREQ_PK)
				op_sim_end("We have too many RREQ packets","please increase the value of MAX_RREQ_PK","in the header block of the cbrp process","");
			stats_nb_rreq++;
		}
	//else
		//nothing to do !!!
}







//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTE REPLY
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Sends a Route Reply associated to the packet "pkptr" (RREQ or DATA)
void send_rrep_pk(Packet* pk_src, Boolean is_gratuitous_rrep){
	Packet*		pk_dest;
	//Info in packet
	int			pk_id;
	int			address_src_init;
	int			address_relay;
	int			address_relay_previous;
	int			address_dest;
	int			stat_id;
	//Control
	char		msg[500];
	int			i;
	char		field_name[200];
	
	pk_dest = op_pk_create_fmt("cbrp_rrep");
	//Copy Relay Fields
	for (i=0; i <= MAX_RELAY_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "RELAY_%d", i);
			if (op_pk_nfd_is_set(pk_src, field_name))
				{
					op_pk_nfd_get(pk_src , field_name, &address_relay);
					op_pk_nfd_set(pk_dest, field_name, address_relay);
					
					//If this relay is us, the precedent relay is the destination (the next hop toward destination of RREP)
					if (address_relay == my_address)
						address_dest = address_relay_previous;
					address_relay_previous = address_relay;
				}
			else
				op_pk_nfd_strip (pk_dest, field_name);
		}
	
	//Source	
	op_pk_nfd_get(pk_src, "PK_ID", 			&pk_id);
	op_pk_nfd_get(pk_src, "SRC_INIT", 		&address_src_init);
	op_pk_nfd_get(pk_src, "STAT_ID", 		&stat_id);
	
	//Dest
	op_pk_nfd_set(pk_dest, "SRC" , 			my_address);
	op_pk_nfd_set(pk_dest, "SRC_INIT" , 	my_address);
	op_pk_nfd_set(pk_dest, "DEST", 			address_dest);
	op_pk_nfd_set(pk_dest, "OPTION_TYPE" , 	RREP_PK_TYPE);
	op_pk_nfd_set(pk_dest, "TTL" , 			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest, "PK_ID" , 		pk_id);

	//Stats (we don't maintain stats for Gratuitous Route Replies, it is less important (and we enter with a conflict with correlation between RREQ and RREP stats)
	if (!is_gratuitous_rrep)
		{
			//No RREP was already sent
			if (stats_rreq [stat_id].rrep_time_reception == 0)
				{
					stats_nb_rrep++;
					stats_rreq [stat_id].dest				= my_address;
					stats_rreq [stat_id].rrep_time_emission	= op_sim_time();
					op_pk_nfd_set(pk_dest, "STAT_ID" , 		stat_id);
				}
		}
	else
		op_pk_nfd_set(pk_dest, "STAT_ID" , -1);

	
	if ((address_dest != my_address) && (address_src_init != my_address))
		{
			//Transmission
			if (ACK_FOR_RREP)
				add_unicast_ack(address_dest , pk_id , pk_dest);
			pk_send(pk_dest);	
	
	
			if(DEBUG>1)
				{
					if (!is_gratuitous_rrep)
						{
							sprintf(msg,"\n!!!!!!!!!!  %d sends a Route Reply to %d at %f !!!!!!!!!!!\n\n", my_address , address_src_init , op_sim_time());
							cbrp_rreq(msg);
							cbrp_rrep(msg);
						}	
					else
						{
							sprintf(msg,"\n!!!!!!!!!!  %d sends a Gratuitous Route Reply to %d at %f !!!!!!!!!!!\n\n", my_address , address_src_init , op_sim_time());
							cbrp_rreq(msg);
							cbrp_rrep(msg);
						}
				}
		}	
}


//Sends a Route Reply for the RREQ "pkptr"
void send_rrep(Packet* pk_src){
	send_rrep_pk(pk_src, OPC_FALSE);
}

//Sends a gratuitous Route Reply for the RREQ "pkptr"
void send_gratuitous_rrep(Packet* pk_src){
	send_rrep_pk(pk_src, OPC_TRUE);
}


//Search the next relay in Relay Fields and sends the RREP to it
void set_dest_rrep_to_next_relay(Packet* pk_src){
	int		address_tmp , address_final;
	int		i;
	char	field_name[200];
	char	msg[500];
	
	//For each relay
	for(i = MAX_RELAY_FIELDS_IN_RREQ_PK; (i>=0) ; i--)
		{
			sprintf(field_name,"RELAY_%d", i);
			if (op_pk_nfd_is_set(pk_src, field_name))
				{
					op_pk_nfd_get(pk_src, field_name, &address_tmp);
					//I found my address -> The next field is the next relay
					if (address_tmp == my_address)
						{
							i--;
							//Gathers the address of the next relay
							sprintf(field_name,"RELAY_%d", i);
							op_pk_nfd_get(pk_src, field_name, &address_tmp);
							op_pk_nfd_set(pk_src, "DEST", address_tmp);											
							return;
						}
					
				}
		}
	
	//No Relay found !!!!!
	if (DEBUG>1)
		{	
			op_pk_nfd_get(pk_src, "RELAY_0", &address_final);
			sprintf(msg,"%d has not found the next relay toward %d\n",my_address, address_final);
			cbrp_rrep(msg);
			printf(msg);			
		}
}


void bypass_me_if_useless_in_rrep(Packet* pkptr){
	//Control
	int		i;
	//Control for packet
	char	field_name[200];
	char	next_field_name[200];
	int		address_temp;
	//Info in packet
	int		my_address_position = -1;
	int		address_previous , address_next;
	
	//I search the position of my address
	for(i=MAX_RELAY_FIELDS_IN_RREQ_PK ; (i>=0) && (my_address_position == -1) ; i--)
		{
			sprintf(field_name, "RELAY_%d", i);
			op_pk_nfd_get(pkptr , field_name , &address_temp);
			if(my_address == address_temp)
				my_address_position = i;
		}
	
	//Next and Previous Relays
	sprintf(field_name,"RELAY_%d",my_address_position + 1);
	op_pk_nfd_get(pkptr , field_name , &address_previous);
	sprintf(field_name,"RELAY_%d",my_address_position - 1);
	op_pk_nfd_get(pkptr , field_name , &address_next);

	//Bypass me if I am useless (I shift all address 1 field lower)
	if (is_integer_present_in_list(get_list_neighbors_associated(address_next),address_previous))
		{
			sprintf(field_name, 	 "RELAY_%d",my_address_position );
			sprintf(next_field_name, "RELAY_%d",my_address_position + 1);

			for(i = my_address_position; (i+1 <= MAX_RELAY_FIELDS_IN_RREQ_PK) && (op_pk_nfd_is_set(pkptr,next_field_name)); i++)
				{
					//shifts values
					op_pk_nfd_get(pkptr , next_field_name, &address_temp);
					op_pk_nfd_set(pkptr , field_name , 	   address_temp);

					sprintf(field_name, 	"RELAY_%d" , i + 1);
					sprintf(next_field_name,"RELAY_%d" , i + 2);
				}
			//"deletes" the last field (useless because the shift)
			op_pk_nfd_strip(pkptr,field_name);
		}
}

//Returns the list of relay toward destination (extracted from the RREP)
List* create_route_from_rrep(Packet* pkptr){
	List	*route;
	int		i;
	int		address_relay;
	char	field_name[200];
	
	//List Initialization
	route	= op_prg_list_create();
	route 	= op_prg_mem_alloc (sizeof(List));

	//For each relay in the packet
	for(i=0; i < MAX_RELAY_FIELDS_IN_RREQ_PK; i++)
		{
			sprintf(field_name,"RELAY_%d",i);

			//Adds the relay in the route
			if(op_pk_nfd_is_set(pkptr, field_name))
				{
					op_pk_nfd_get(pkptr, field_name, &address_relay);
					add_integer_in_list(route, address_relay);
				}
			else
				return(route);
		}
	
	//We hast just the number of relay max, but the route is valid
	return(route);
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTE ERROR
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

int get_last_relay(Packet * pkptr){
	//Control
	int			i;
	char		field_name[200];
	int			address_relay = 0;
	
	for (i=0; i <= MAX_RELAY_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "RELAY_%d", i);

			if (op_pk_nfd_is_set(pkptr, field_name))
				op_pk_nfd_get(pkptr , field_name, &address_relay);
			else if (address_relay != 0)
				return (address_relay);
			else
				return(-1);
		}
}

//Sends a Route Error for the pk "pkptr"
void send_rerr(Packet* pk_src){
	Packet*		pk_dest;
	//Info in packet
	int			address_src_init;
	int			address_relay;	
	int			address_relay_previous;
	int			address_dest;
	int			address_dest_final;
	//Control
	char		msg[500];
	int			i;
	char		field_name[200];
	
	pk_dest = op_pk_create_fmt("cbrp_rerr");
	//Copy Relay Fields
	for (i=0; i <= MAX_RELAY_FIELDS_IN_RREQ_PK ; i++)
		{
			sprintf(field_name , "RELAY_%d", i);

			if (op_pk_nfd_is_set(pk_src, field_name))
				{
					op_pk_nfd_get(pk_src , field_name, &address_relay);
					op_pk_nfd_set(pk_dest, field_name, address_relay);
					
					//If this relay is us, the precedent relay is the destination (the next hop toward destination of RERR)
					if (address_relay == my_address)
						address_dest = address_relay_previous;
					address_relay_previous = address_relay;
				}
			else
				op_pk_nfd_strip (pk_dest, field_name);
		}
	
	//Source	
	op_pk_nfd_get(pk_src, "SRC_INIT", 		&address_src_init);
	op_pk_nfd_get(pk_src, "DEST_FINAL", 	&address_dest_final);
	
	//Dest
	op_pk_nfd_set(pk_dest, "SRC" , 			my_address);
	op_pk_nfd_set(pk_dest, "SRC_INIT" , 	my_address);
	op_pk_nfd_set(pk_dest, "DEST", 			address_dest);
	op_pk_nfd_set(pk_dest, "DEST_FINAL", 	address_src_init);
	op_pk_nfd_set(pk_dest, "OPTION_TYPE" , 	RERR_PK_TYPE);
	op_pk_nfd_set(pk_dest, "TTL" , 			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest, "PK_ID" , 		current_id++);
	op_pk_nfd_set(pk_dest, "STAT_ID" , 		stats_nb_rerr);

	//Transmission
	if (ACK_FOR_RERR)
		add_unicast_ack(address_dest , current_id-1 , pk_dest);
	pk_send(pk_dest);
	
	
	//Stats
	if (stats_nb_rerr > MAX_RERR_PK)
		op_sim_end("We have too many rerr packets","please increase the value of MAX_RERR_PK","in the header block of the cbrp process","");
	stats_rerr [stats_nb_rerr].source			= my_address;
	stats_rerr [stats_nb_rerr].data_dest		= address_dest_final;
	stats_rerr [stats_nb_rerr].time_emission	= op_sim_time();
	stats_nb_rerr++;

	if(DEBUG>1)
		{
			sprintf(msg,"\n!!!!!!!!!!  %d sends a Route Error to %d via %d at %f !!!!!!!!!!!\n\n",my_address , address_src_init ,  address_dest , op_sim_time());
			cbrp_data(msg);
			cbrp_rerr(msg);
		}	
}





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DATA
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Timeout entries in data pk buffer
void delete_timeout_in_data_pk_buffer(){
	int					i = 0;
	struct_pk_buffer*	entry;
	char				msg[500];
	
	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		return;
	
	//For each entry
	for (i=op_prg_list_size(data_pk_buffer)-1; i >=0; i--)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			//We delete the entry
			if (entry->timeout < op_sim_time())
				{				
					//DEBUG
					if (DEBUG>2)
						{
							sprintf(msg,"DATA-BUFFER : deletes the packet to %d with timeout %f at %f\n", entry->dest , entry->timeout , op_sim_time());
							cbrp_debug(msg);
							cbrp_data(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( data_pk_buffer , i);
					free(entry);
				}
		}
}

//Add the data packet in the buffered list
void add_in_data_pk_buffer(Packet *pk_dest){
	struct_pk_buffer*	entry;
	int					dest;
	
	op_pk_nfd_get(pk_dest, "DEST_FINAL",&dest);
	
	//Memory allocation
	entry = (struct_pk_buffer*) malloc (sizeof(struct_pk_buffer));
			
	//Info
	entry->packet	= op_pk_copy(pk_dest);
	entry->timeout	= op_sim_time() + TIMEOUT_DATA_PK_BUFFER;
	entry->dest		= dest;
	
	//I add it in the list
	op_prg_list_insert(data_pk_buffer, entry , OPC_LISTPOS_TAIL);	
}

//Fill all relay fields with the valid route
void fill_relay_fields_for_data_pk(Packet* pkptr , List* route){
	char		field_name[200];
	int			i , j;
	int			*address_relay;
	
	//If the route is empty, the destination is one of our neighbors
	if (op_prg_list_size(route) == 0)
		return;
	
	//Fill each relay
	for(i=0; i < op_prg_list_size(route); i++)
		{
			//Gets the relay in the list
			address_relay = (int*) op_prg_list_access(route, i);

			//Set it in packet	
			sprintf(field_name,"RELAY_%d",i);
			op_pk_nfd_set(pkptr, field_name, *address_relay);
		}
	for(j=i ; j <= MAX_RELAY_FIELDS_IN_RREQ_PK; j++)
		{
			sprintf(field_name,"RELAY_%d",j);
			op_pk_nfd_strip(pkptr, field_name);
		}
}

//Purge all relay fields (null value)
void purge_useless_relay_fields_in_pk(Packet* pkptr, int max_nb_fields){
	int		i;
	char	field_name[200];

	for(i=0; i <= max_nb_fields; i++)
		{
			sprintf(field_name, "RELAY_%d", i);

			if (op_pk_nfd_is_set(pkptr,field_name))
				op_pk_nfd_strip(pkptr, field_name);
		}
}

//Sends a data packet to destination dest
void send_data(int dest , int code){
	Packet*			pk_dest;
	int				next_relay;
	struct_routing	*struct_dest;
	char			msg[500];
	Boolean			is_pk_sent = OPC_FALSE;
	double			pk_size;

	
	//If I am my own destination, I don't send the data packet
	if (dest == my_address)
		return;
	
	//Common Fields
	pk_dest = op_pk_create_fmt("cbrp_data");
	op_pk_nfd_set(pk_dest, "SRC" , 			my_address);
	op_pk_nfd_set(pk_dest, "SRC_INIT" , 	my_address);
	op_pk_nfd_set(pk_dest, "DEST_FINAL" , 	dest);
	op_pk_nfd_set(pk_dest, "OPTION_TYPE" , 	DATA_PK_TYPE);
	op_pk_nfd_set(pk_dest, "TTL" , 			MAX_NETWORK_RADIUS);	
	op_pk_nfd_set(pk_dest, "PK_ID" , 		current_id++);
	op_pk_nfd_set(pk_dest, "STAT_ID" , 		current_id_data);
	op_pk_nfd_set(pk_dest, "NB_REPAIRS" ,	0);
	
	//Data (256*32 bits)
	op_pk_bulk_size_set(pk_dest , (int) op_dist_exponential( (double)DATA_PK_SIZE * 8)  );
	pk_size = op_pk_bulk_size_get(pk_dest);

	//Is the destination direct neighbor ?
	struct_dest = get_routing_entry(dest);
	if (struct_dest != NULL)
		{
			//The destination is neighbors -> direct transmission   -- OR --   the destination has a route in the routing_table
			if (struct_dest->hops == 1)
				{
					//Set "good" relay fields
					purge_useless_relay_fields_in_pk(pk_dest , MAX_RELAY_FIELDS_IN_RREQ_PK);
					add_in_relay_fields(pk_dest , my_address);
					add_in_relay_fields(pk_dest , dest);
					
					//Set dest field
					op_pk_nfd_set(pk_dest, "DEST", struct_dest->dest);
					
					//Is the next hop a bidirect neighbor ?
					if (is_bidirect_neighbor(struct_dest->dest))
						next_relay = struct_dest->dest;
					else
						next_relay = -1;
				}
			else
				{
					fill_relay_fields_for_data_pk(pk_dest , struct_dest->route);
					op_pk_nfd_get(pk_dest, "RELAY_1", 	&next_relay);
					op_pk_nfd_set(pk_dest, "DEST", 		next_relay);
				}
			
			//Transmission
			if (next_relay > 0)
				{
					is_pk_sent = OPC_TRUE;
					if (ACK_FOR_DATA)
						add_unicast_ack(next_relay , current_id-1 , pk_dest);
					add_address_id_couple(my_address , current_id-1);
					pk_send(pk_dest);
			
					//DEBUG
					if (DEBUG>1)
						{
							sprintf(msg,"\n\n-------  DATA-PK : data-pk from %d to %d via %d at %f  (pk_id %d, without RREQ) -------\n", my_address , dest , next_relay , op_sim_time() , current_id-1);
							cbrp_data(msg);
						}
				}
		}
	if ((struct_dest == NULL) || (next_relay <= 0))
		{
			//Route Request + Buffer of data packet
			if (!entry_exists_in_rreq_pk_buffer(dest))
				send_rreq(dest);
			add_in_data_pk_buffer(pk_dest);
		}
	
	//Stats
	if (stats_nb_data_pk > MAX_DATA_PK)
		op_sim_end("We have too many data packets","please increase the value of MAX_DATA_PK","in the header block of the cbrp process","");

	stats_data_pk	[stats_nb_data_pk].source			= my_address;
	stats_data_pk	[stats_nb_data_pk].dest				= dest;
	stats_data_pk 	[stats_nb_data_pk].time_generation	= op_sim_time();
	stats_data_pk 	[stats_nb_data_pk].pk_size			= (int)pk_size;
	if (is_pk_sent)
			stats_data_pk [stats_nb_data_pk].time_emission	= op_sim_time();
	sprintf(stats_data_pk [stats_nb_data_pk].route, "%d ", my_address);
	op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stats_nb_data_pk].src_x_pos));	
	op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stats_nb_data_pk].src_y_pos));	

	//Control & Stats
	current_id_data++;	
	stats_nb_data_pk++;
}


Boolean send_data_pk_buffer(int destination){
	int					i = 0;
	struct_pk_buffer*	entry;
	char				msg[500];
	struct_routing		*struct_dest;
	int					next_relay;
	Boolean				is_found = OPC_FALSE;
	int					pk_id;
	int					stat_id;
	
	
	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		return(OPC_FALSE);
	
	//Search if the entry already exists
	for (i=op_prg_list_size(data_pk_buffer)-1 ; i>=0 ;i--)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			//We delete the entry
			if (entry->dest == destination)
				{	
					//The loop is valid
					is_found = OPC_TRUE;
				
					//Gets the relay
					struct_dest = get_routing_entry(entry->dest);
					next_relay = -1;
					op_pk_nfd_get(entry->packet, "PK_ID", &pk_id);
					if (struct_dest!= NULL)
						{
							op_pk_nfd_get(entry->packet , "STAT_ID", &stat_id);
							stats_data_pk [stat_id].time_emission = op_sim_time();
						
							//The destination is neighbors -> direct transmission   -- OR --   the destination has a route in the routing_table
							if ((struct_dest->hops == 1) && (struct_dest->bidirect))
								{
									//Set good relay fields
									purge_useless_relay_fields_in_pk(entry->packet , MAX_RELAY_FIELDS_IN_RREQ_PK);
									add_in_relay_fields(entry->packet , my_address);
									add_in_relay_fields(entry->packet , struct_dest->dest);
									
									//dest Field
									op_pk_nfd_set(entry->packet, "DEST", struct_dest->dest);
									
									//Next relay is direct
									next_relay = struct_dest->dest;
								}
							else
								{
									fill_relay_fields_for_data_pk(entry->packet , struct_dest->route);
									//next_relay = struct_dest->relay;
									op_pk_nfd_get(entry->packet, "RELAY_1", 	&next_relay);
									op_pk_nfd_set(entry->packet, "DEST", 		next_relay);
								}

							//Transmission
							if (ACK_FOR_DATA)
								add_unicast_ack(next_relay , pk_id , entry->packet);
							add_address_id_couple(my_address , pk_id);
							pk_send(entry->packet);
						}
			
					//DEBUG
					if (DEBUG>2)
						{
							sprintf(msg,"\n\n-------  DATA-PK : data-pk from %d to %d via %d at %f (timeout %f and pk_id %d)  (with at least 1 RREQ)   -------\n", my_address , entry->dest , next_relay , op_sim_time(), entry->timeout , pk_id);
							cbrp_data(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( data_pk_buffer , i);
					free(entry);
				}
		}
	
	return(is_found);

}


int set_dest_data_to_next_relay(Packet* pk_dest){
	int		address_tmp , address_final;
	int		i;
	char	field_name[200];
	char	msg[500];
	
	//For each relay
	for(i = 0 ; i < MAX_RELAY_FIELDS_IN_RREQ_PK; i++)
		{
			sprintf(field_name,"RELAY_%d", i);

			if (op_pk_nfd_is_set(pk_dest, field_name))
				{
					op_pk_nfd_get(pk_dest, field_name, &address_tmp);
					
					//I found my address -> The next field is the next relay
					if (address_tmp == my_address)
						{
							i++;
							//Gathers the address of the next relay
							sprintf(field_name,"RELAY_%d", i);
							op_pk_nfd_get(pk_dest, field_name, &address_tmp);
							op_pk_nfd_set(pk_dest, "DEST", address_tmp);											
							return (address_tmp);
						}
					
				}
		}
	
	//No Relay found !!!!!
	if (DEBUG>1)
		{	
			//Message
			op_pk_nfd_get(pk_dest, "DEST_FINAL", &address_final);
			sprintf(msg,"%d has not found the next relay toward %d for a data packet\n",my_address, address_final);
			cbrp_data(msg);
		}
	return(OPC_FALSE);	
}

//Add a relay field after me in a packet
void add_new_relay_after_me(Packet* pk_dest, int relay){
	int		addr_tmp , address_final;
	int		i , j;
	char	field_name[200];
	char	msg[500];
	
	//For each relay
	for(i = 0 ; i < MAX_RELAY_FIELDS_IN_RREQ_PK; i++)
		{
			sprintf(field_name,"RELAY_%d", i);

			if (op_pk_nfd_is_set(pk_dest, field_name))
				{
					op_pk_nfd_get(pk_dest, field_name, &addr_tmp);
					
					//I found my address -> The next field is the next relay
					if (addr_tmp == my_address)
						{
							i++;
							//Shift all relays from end to the "good position"
							for (j=MAX_RELAY_FIELDS_IN_RREQ_PK; j>=i+1 ; j--)
								{								
									sprintf(field_name,"RELAY_%d",j-1);

									if (op_pk_nfd_is_set(pk_dest , field_name))
										{
											op_pk_nfd_get(pk_dest , field_name , &addr_tmp);
											sprintf(field_name,"RELAY_%d",j);
											op_pk_nfd_set(pk_dest , field_name , addr_tmp);
										}
								
								}
							sprintf(field_name, "RELAY_%d", i);
							op_pk_nfd_set(pk_dest , field_name, relay);
							
							return;							
						}					
				}
		}
	
	//Pb : we didn't find ourself in relay fields
	if (DEBUG>1)
		{	
			//Message
			op_pk_nfd_get(pk_dest, "DEST_FINAL", &address_final);
			op_pk_print(pk_dest);
			sprintf(msg,"%d has not found itself in a DATA Packet toward %d !!!\n",my_address, address_final);
			print_routing_table();
			print_routes();
			cbrp_data(msg);
			printf(msg);
		}
}

//A Route Errpr occured, we must send a RERR or find a new route (next hop will contain the new computed relay)
Boolean handle_route_error_for_data(Packet* pk_src, int* next_hop){
	int		new_relay;
	int		dest_final;
	char	msg[500];
	int		address_src_init;
	int		nb_repairs;
	int		stat_id;
	
	//packet Info
	op_pk_nfd_get(pk_src, "SRC_INIT", 	&address_src_init);	
	op_pk_nfd_get(pk_src, "DEST_FINAL", 	&dest_final);
	op_pk_nfd_get(pk_src, "NB_REPAIRS", 	&nb_repairs);
	op_pk_nfd_get(pk_src, "STAT_ID", 	&stat_id);
	
	//Search a new relay toward the next hop
	new_relay = get_new_relay_toward(*next_hop);
	if ((new_relay != -1) && (nb_repairs < MAX_NB_LOCAL_REPAIRS_FOR_DATA))
		{
			//Modify he route in packet			
			add_new_relay_after_me(pk_src , new_relay);			
			op_pk_nfd_set(pk_src, "NB_REPAIRS", 	nb_repairs+1);
			
			//Send a Gratuitous RREP
			send_gratuitous_rrep(pk_src);
			
			if (DEBUG>1)
				{
					sprintf(msg, "RERR (local repair no %d) : %d relayed to %d to join next relay %d (the data packet is from %d for %d, stat_id %d) at %f\n", nb_repairs +1 , my_address , new_relay , *next_hop , address_src_init , dest_final , stat_id , op_sim_time());
					cbrp_debug (msg);
					cbrp_data (msg);
				}
			
			*next_hop = new_relay;
			return(OPC_TRUE);		
		}
	//We must generate a route error, and we drop the packet
	else if (address_src_init != my_address)
		{
			//Sends a route error
			send_rerr(pk_src);
			
			if (DEBUG>1)
				{
					sprintf(msg, "RERR (in relaying)  : %d has not found any node to join next relay %d (the data packet is from %d for %d with %d nb local repairs, stat_id %d) at %f\n", my_address , *next_hop , address_src_init , dest_final , nb_repairs , stat_id , op_sim_time());
					cbrp_debug (msg);
					cbrp_data (msg);
				}
			
			return(OPC_FALSE);
		}
	else 
		{
			//Delete the obsolete route
			delete_route(dest_final);
			
			//Debug
			if (DEBUG>1)
				{
					sprintf(msg,"-------- RERR (from source) : in %d for a data pk from %d toward %d at %f  --------\n" , my_address , address_src_init , dest_final , op_sim_time());
					cbrp_data(msg);
					cbrp_rerr(msg);
				}
			return(OPC_FALSE);
		}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								DEBUG
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void cbrp_rreq(char* msg){
	FILE*	file;
	char	str[50];
	
	if  (!DEBUG_CONTROL)
		return;
	
	sprintf(str,"results_cbrp/%d_cbrp_rreq.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void cbrp_rerr(char* msg){
	FILE*	file;
	char	str[50];
	
	if  (!DEBUG_CONTROL)
		return;
	
	sprintf(str,"results_cbrp/%d_cbrp_rerr.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void cbrp_rrep(char* msg){
	FILE*	file;
	char	str[50];
	
	if  (!DEBUG_CONTROL)
		return;
	
	sprintf(str,"results_cbrp/%d_cbrp_rrep.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}	

void cbrp_test(char* msg){
	FILE*	file;
	char	str[50];
	
	if  (!DEBUG_CONTROL)
		return;
	
	sprintf(str,"results_cbrp/%d_cbrp_test.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}	

void cbrp_data(char* msg){
	FILE*	file;
	char	str[50];
	
	if  (!DEBUG_DATA)
		return;
	
	sprintf(str,"results_cbrp/%d_cbrp_data.txt",begin_time);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void cbrp_debug(char* msg){
	FILE*	file;
	char	str[50];
	
	if (my_address<10)
		sprintf(str,"results_cbrp/details_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(str,"results_cbrp/details_per_node/results_%d.txt",my_address);
	file = fopen(str,"a");
	fprintf(file,msg);
	fclose(file);
}

void print_stats_cluster_global(){
	char				msg[500];
	struct_stats_cl*	entry;
	int					i;

	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("CLUSTER GLOBAL :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("    Source	|   Cluster1|	Cluster2	|	Timeout \n");

	if (op_prg_list_size(stats_cluster_global) != 0)
		{
			for (i=0 ; i < op_prg_list_size(stats_cluster_global) ; i++)
				{
					entry = (struct_stats_cl*) op_prg_list_access (stats_cluster_global, i);
					sprintf(msg, "	%d	|	%d	|	     %d	|	%f\n", entry->src , entry->addr1 , entry->addr2 , entry->timeout);
					cbrp_debug(msg);
				}
		}
	
	cbrp_debug ("\n\n\n");
}

void print_stats_cluster_local(){
	char	msg[500];
	int*	entry;
	int		i;

	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("CLUSTER LOCAL :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");

	//Initialization
	cbrp_debug ("List of Cluster Neighbors of My cluster : \n");

	if (op_prg_list_size(stats_cluster_local) != 0)
		{
			for (i=0 ; i < op_prg_list_size(stats_cluster_local) ; i++)
				{
					entry = (int*) op_prg_list_access (stats_cluster_local, i);
					sprintf(msg, "%d	|	", *entry);
					cbrp_debug(msg);
				}
		}
	
	cbrp_debug ("\n\n\n");
}

void print_cluster_gw(){
	char				msg[500];
	struct_cluster_gw*	entry;
	int					i;

	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("CLUSTER GW :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");

	//Initialization
	cbrp_debug ("List of Clusters for which I am a gateway:\n  Cluster	|   Timeout \n");

	if (op_prg_list_size(cluster_gw) != 0)
		{
			for (i=0 ; i < op_prg_list_size(cluster_gw) ; i++)
				{
					entry = (struct_cluster_gw*) op_prg_list_access (cluster_gw, i);
					sprintf(msg, "	%d	|	%f\n", entry->cluster , entry->timeout);
					cbrp_debug(msg);
				}
		}
	
	cbrp_debug ("\n\n\n");
}

void print_cluster_neighbor_gw(){
	char				msg[500];
	struct_cl_neigh*	entry;
	int					i;

	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("CLUSTER NEIGHBORS - GATEWAYS (FOR CLUSTERHEADS ONLY) :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");

	//Initialization
	cbrp_debug ("For CLUSTERHEAD : List of my gateways and their Cluster-Neighbors:\n    Cluster	|   Gateway	|	Timeout \n");

	if (op_prg_list_size(cluster_neighbors) != 0)
		{
			for (i=0 ; i < op_prg_list_size(cluster_neighbors) ; i++)
				{
					entry = (struct_cl_neigh*) op_prg_list_access (cluster_neighbors, i);
					sprintf(msg, "	%d	|	%d	|	%f\n", entry->cluster , entry->gw , entry->timeout);
					cbrp_debug(msg);
				}
		}
	
	cbrp_debug ("\n\n\n");
}

void print_cluster_info(){
	char				msg[500];

	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("CLUSTER INFO :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");

	
	sprintf(msg, "Clusterhead : %d\n",my_cluster.clusterhead);
	cbrp_debug (msg);
	
	cbrp_debug ("\n\n\n");
}

void print_addr_pk_id_list(){
	int					i=0;
	struct_addr_pk_id*	couple;
	char				msg[500];
	
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("ID TABLE :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("Source	|   Pk Id	|	Timeout \n");
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(addr_pk_id_list)==0)
		{
			cbrp_debug ("\n\n\n");
			return ;
		}	
	
	//For each entry of the list
	for(i=0; i< op_prg_list_size(addr_pk_id_list);i++)
		{  
			couple = (struct_addr_pk_id*) op_prg_list_access(addr_pk_id_list,i);
			//.....compare it
			sprintf(msg,"	%d	|	%d	|	%f\n",couple->address , couple->pk_id , couple->timeout);
			cbrp_debug(msg);
		}
	cbrp_debug ("\n\n\n");
}

void print_routes(){
	struct_routing*		entry;
	int					i , j;
	char				msg[500];
	int*				address_relay;	
	
	//Updates the table
	delete_timeout_in_routing_table();
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("ROUTES TABLE :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("Destination	|	Timeout		|   Relay0	|   Relay1	|   Relay2	|   Relay3	|   Relay4	|	...	 \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(routing_table)==0)
		{
			cbrp_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if ((entry!=NULL) && (entry->hops>1))
				{
					sprintf(msg,"%d		|	%f	",entry->dest , entry->timeout);					
					for(j=0; j< op_prg_list_size(entry->route);j++)
						{
							address_relay = (int*) op_prg_list_access(entry->route, j);
							sprintf(msg,"%s|	%d	",msg,*address_relay);
						}
					sprintf(msg,"%s\n",msg);
					cbrp_debug (msg);
				}
		}
	cbrp_debug ("\n\n\n");

}

void print_routing_table(){
	struct_routing*		entry;
	int					i;
	char				msg[500];
	
	//Updates the table
	delete_timeout_in_routing_table();
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("ROUTING TABLE :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("Destination	|   Relay	|   Hops	|   Weight	|Clusterhead|  Bidirect	|	Timeout \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(routing_table)==0)
		{
			cbrp_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(routing_table) ; i++)
		{
			//gets the entry
			entry = (struct_routing*) op_prg_list_access (routing_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if (entry!=NULL)
				{
					//Prints it
					sprintf(msg,"	%d	|	%d	|	%d	|	%d	|	%d	|	%d	|	%f \n" , entry->dest , entry->relay , entry->hops , entry->weight , entry->clusterhead, entry->bidirect , entry->timeout);
					cbrp_debug (msg);
				}
		}
	cbrp_debug ("\n\n\n");
}



void print_ack_table(){
	struct_ack*		entry;
	int				i;
	char			msg[500];
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("ACK TABLE :\n");		
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("Destination	|   Pk_id	|	Nb Retries	|     Timeout \n");
	
	
	//If the list is empty, I exit the function
	if (op_prg_list_size(ack_table)==0)
		{
			cbrp_debug ("\n\n\n");
			return ;
		}
	
	//For each entry
	for (i=0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			entry = (struct_ack*) op_prg_list_access (ack_table, i);

			//Useless, but avoid a 'memory access error' if there is a bug
			if (entry!=NULL)
				{
					//Prints it
					sprintf(msg,"	%d	|	%d	|		%d	|	%f \n" , entry->dest , entry->pk_id , entry->nb_retry , entry->timeout);
					cbrp_debug (msg);
				}
		}
	cbrp_debug ("\n\n\n");
}


void print_neighbors(){
	int					i , j ;
	struct_routing		*routing_entry;
	int					*neighbor_entry;
	char				msg[500];
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("NEIGHBORS TABLE  :\n");
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("|	1-Neighbor	:	List of its 1-Neighbors\n");
	
	
	//If the list is empty
	if (op_prg_list_size(routing_table)==0)
		{
			cbrp_debug ("\n\n\n");
			return;
		}
	
	//Search the entry
	for (i=0 ; i < op_prg_list_size(routing_table); i++)
		{
			//gets the entry
			routing_entry = (struct_routing*) op_prg_list_access (routing_table, i);
			
			sprintf(msg, "|	Node %d	:", routing_entry->dest);
			cbrp_debug(msg);
			
			//Print all its neighbors
			for (j=0 ; j < op_prg_list_size(routing_entry->neighbors); j++)
				{
					//gets the entry
					neighbor_entry = (int*) op_prg_list_access (routing_entry->neighbors, j);
		
					sprintf(msg, "	%d	|",*neighbor_entry);
					cbrp_debug(msg);
				}
			cbrp_debug("\n");
		}
	cbrp_debug ("\n\n\n");
}

void print_rreq_pk_buffer(){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[500];
	double					older_entry=-1;
	
		
	//Common Information
	cbrp_debug ("-------------------------------------------------------------------------\n");
	cbrp_debug ("RREQ PK BUFFER  :\n");
	cbrp_debug ("-------------------------------------------------------------------------\n\n");
	
	cbrp_debug ("Destination	|	Nb_Retry		|	Stat_Id		|	Timeout\n");
	
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		{
			cbrp_debug ("\n\n\n");
			return;
		}

	//Search if the entry already exists
	for (i=0 ; i < op_prg_list_size(rreq_pk_buffer) ; i++)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			sprintf(msg, "%d		|	%d	|	%d	|	%f\n", entry->dest , entry->nb_retry , entry->stat_id , entry->timeout);
			cbrp_debug(msg);
		}
	cbrp_debug ("\n\n\n");
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								STATISTICS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------



//----------------------------------------------------------------
//				Individual Final Stats
//----------------------------------------------------------------

void individual_statistics_generate(){
	char	msg[500];
	
	
	sprintf(msg,"\n\n---------------------- END - %f seconds -------------------------\n\n\n",op_sim_time());
	cbrp_debug(msg);
	
	print_cluster_info();
	print_cluster_gw();
	print_cluster_neighbor_gw();
	print_routes();
	print_routing_table();	
	//print_ack_table();
	//print_addr_pk_id_list();
	print_stats_cluster_local();
	//print_stats_cluster_global();
}


    

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void cbrp_process (void);
	Compcode cbrp_process_init (void **);
	void cbrp_process_diag (void);
	void cbrp_process_terminate (void);
	void cbrp_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
cbrp_process (void)
	{
	int _block_origin = 0;
	FIN (cbrp_process ());
	if (1)
		{
		/* Variables used in state transitions.		*/
		int			intrpt_code;


		FSM_ENTER (cbrp_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "Init", "cbrp_process () [Init enter execs]")
				{
				//Addresses
				int			addr_attribution;
				char		str[500];
				
				
				
				//Synchronisation with lower levels
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC,0);
				
				//Gets the time of simulation beginning
				if (begin_time==0)
					begin_time = time(NULL);
				
				
				
				
				//----------------------------------------------------
				//
				//					My address
				//
				//-----------------------------------------------------
				
				op_ima_obj_attr_get(op_id_self(),"Address_Attribution",&addr_attribution); 
				switch(addr_attribution){
						case ADDR_RANDOM :
							//I pick-up my wlan mac address
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							my_address = nb_aps + 1 + op_dist_uniform(LOWER_ADDR_FOR_MULTICAST - nb_aps);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_WLAN :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()),"Wireless LAN MAC Address",&my_address);
							op_ima_obj_attr_set(op_id_self(),"My_Address",my_address); 	
						break;
						
						case ADDR_CONFIGURED :
							op_ima_obj_attr_get(op_id_self(),"My_Address",&my_address); 	
						break;
						
						case ADDR_MAC_CDCL_FROM_NAME :
							op_ima_obj_attr_get(op_topo_parent(op_id_self()) , "name" , str);
							my_address = atoi(str);
							op_ima_obj_attr_set(op_topo_parent(op_id_self()),"Wireless LAN MAC Address", my_address);
							op_ima_obj_attr_set(op_id_self() , "My_Address" , my_address); 	
						break;
						
						default :
							op_sim_end("The address auto-configuration is not well-configured" , "", "", "");
						break;
					}
				if (my_address==0)
					op_sim_end("Error : we have a null address","Probable Problem with random address and/or with Mac and Ad-hoc Addresses cohabitation) \n","","");
				
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,cbrp_process)


			/** state (Init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "Init", "cbrp_process () [Init exit execs]")
				{
				}


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init", "INIT_AFTER_MAC")
				/*---------------------------------------------------------*/



			/** state (INIT_AFTER_MAC) enter executives **/
			FSM_STATE_ENTER_FORCED (1, state1_enter_exec, "INIT_AFTER_MAC", "cbrp_process () [INIT_AFTER_MAC enter execs]")
				{
				List 		*liste;
				//Control
				int			addr_attribution;
				char		str[100];
				FILE		*file;
				int 		i,j, addr; 
				char		msg[500];
				//Topology
				char		var_name[200];
				int			nb_fixed_nodes , nb_mobile_nodes , is_node_AP;
				//AP Position
				int			process_id , node_id;
				double		XMAX , YMAX;
				int			MOBILITY_MODEL;
				
				
				
				
				//----------------------------------------------------
				//
				//					TOPOLOGY
				//
				//-----------------------------------------------------
				
				op_ima_obj_attr_get(op_id_self(), "is_AP", &is_AP);
				if (is_AP)
					nb_aps++;
				
				//NB :   AP / normal nodes
				if (nb_nodes == 0)
					{
						//NB :   AP / normal nodes
						nb_fixed_nodes 		= op_topo_object_count(OPC_OBJTYPE_NDFIX);
						for(i=0 ; i<nb_fixed_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDFIX , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_ID_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
				
						nb_mobile_nodes 	= op_topo_object_count(OPC_OBJTYPE_NDMOB);
						for(i=0 ; i<nb_mobile_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDMOB , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_ID_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//	Recuperation of simulation parameters
				//
				//-----------------------------------------------------
				
				//The simulation paramaters
				//For this Node
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG",				&DEBUG);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_CONTROL",		&DEBUG_CONTROL);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_DATA", 			&DEBUG_DATA);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_LOAD", 			&DEBUG_LOAD);
				op_ima_sim_attr_get (OPC_IMA_INTEGER, 	"DEBUG_TOPO", 			&DEBUG_TOPO);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_CONNECTIONS", 		&NB_CONNECTIONS);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"DATA_PK_SIZE", 		&DATA_PK_SIZE);
				op_ima_sim_attr_get (OPC_IMA_DOUBLE,	"INTERARRIVAL_DATA_PK", &INTERARRIVAL_DATA_PK);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"NB_PK_PER_FLOW", 		&NB_PK_PER_FLOW);
				op_ima_sim_attr_get (OPC_IMA_INTEGER,	"ACK_FOR_DATA", 		&ACK_FOR_DATA);
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				POSITION OF THE AP
				//
				//-----------------------------------------------------
				
				
				//The AP is central only if it exists one single AP
				if ((is_AP) && (nb_aps_expected == 1))
					{
						process_id = op_id_self();
						node_id = op_topo_parent (process_id);
						op_ima_sim_attr_get(OPC_IMA_INTEGER, 	"SP_LOW_MOBILITY_MODEL"	, &MOBILITY_MODEL);
						
				
						//NB : NEITHER_POSITION_NOR_MOBILITY = 5
						if (MOBILITY_MODEL != 5)
							{
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX"  , &XMAX);
								op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX"  , &YMAX);
								op_ima_obj_attr_set(node_id, "x position", XMAX/2);
								op_ima_obj_attr_set(node_id, "y position", YMAX/2);
							}
					}
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//				General Infos
				//
				//-----------------------------------------------------
				
				//--------------- Various ---------------
				
				current_id 						= op_dist_uniform(30000);				//the first id of the packet I will send
				
				
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//		Open the file for out messages
				//
				//-----------------------------------------------------
				
				//-------- protection against arrays overflows -------
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the cdcl_routing process","");
				if (nb_nodes >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the cdcl_routing process","");
				
				//----------------------- Stats ---------------------
				my_stat_id = nb_nodes++;							//The first node has id 0
				address_to_stat_id	[my_address] = my_stat_id;		//Convert an address into an id
				stat_id_to_address	[my_stat_id] = my_address;		//The inverse
				
				
				//--------------------- Per node --------------------
				
				if (my_address<10)
					sprintf(str,"results_cbrp/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
					sprintf(str,"results_cbrp/details_per_node/results_%d.txt",my_address);
				file = fopen(str,"w");
				fclose(file);
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id==0)
					{
						//Stats About Data Packets
						for(i=0; i < MAX_DATA_PK ; i++)
							{
								stats_data_pk	[i].source 				= 0;
								stats_data_pk	[i].dest 				= 0;
								stats_data_pk	[i].pk_size 			= 0;
								stats_data_pk	[i].hops 				= 0;
								stats_data_pk	[i].nb_retry 			= 0;
								stats_data_pk 	[i].time_emission 		= 0;
								stats_data_pk 	[i].time_reception		= 0;
							}
						//Stats About RREQ/RREP Packets
						for(i=0; i < MAX_RREQ_PK ; i++)
							{
								stats_rreq	[i].source					= 0;
								stats_rreq	[i].dest					= 0;
								stats_rreq	[i].rreq_time_emission		= 0;
								stats_rreq	[i].rreq_time_reception		= 0;
								stats_rreq	[i].rreq_nb_retry			= 0;
								stats_rreq	[i].rrep_time_emission		= 0;
								stats_rreq	[i].rrep_time_reception		= 0;
								stats_rreq	[i].rrep_hops				= 0;
								stats_rreq	[i].rrep_nb_retry			= 0;
								for (j=0; j < MAX_NB_NODES ; j++)
									{
										stats_rreq[i].rreq_is_rcvd [i];
										stats_rreq[i].rreq_is_ch [j];
									}					  
							}
						//Stats About RERR Packets
						for(i=0; i < MAX_RERR_PK ; i++)
							{
								stats_rerr	[i].time_emission		= 0;
								stats_rerr	[i].time_reception		= 0;
								stats_rerr	[i].source				= 0;
								stats_rerr	[i].dest				= 0;
								stats_rerr	[i].data_dest			= 0;
								stats_rerr	[i].hops				= 0;
								stats_rerr	[i].nb_retry			= 0;
							}
						if (DEBUG_CONTROL)
							{
								sprintf(str,"results_cbrp/%d_cbrp_rrep.txt",begin_time);		
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#                DEBUG for Route Replies in CBRP                 #\n");
								fprintf(file,"##################################################################\n");
								fclose(file);
								sprintf(str,"results_cbrp/%d_cbrp_rreq.txt",begin_time);		
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#                DEBUG for Route Requests in CBRP                #\n");
								fprintf(file,"##################################################################\n");
								fclose(file);
							}		
						if  (DEBUG_DATA)
							{
								sprintf(str,"results_cbrp/%d_cbrp_data.txt",begin_time);		
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#        DEBUG for DATA Packets Emission/Reception in CBRP       #\n");
								fprintf(file,"##################################################################\n");
								fclose(file);
							}
						if  (DEBUG_LOAD)
							{
								sprintf(str,"results_cbrp/%d_cbrp_network_control.txt",begin_time);
								file = fopen(str,"w");
								fprintf(file,"##################################################################\n");
								fprintf(file,"#               DEBUG for Flows Overheads in CBRP                #\n");
								fprintf(file,"##################################################################\n");
								fprintf(file , "# All flows are in packets per second per node (RET signifies 'Retransmission')\n");
								fprintf(file , "TIME		| 	ACKS		|	HELLO		|	DATA		|	DATA RET	|	RREQ	|	RREP\n");
								fclose(file);
							}
						
					}
				
				
				
				
				
				//----------------------------------------------------
				//
				//			LISTS INTIALIZATIONS
				//
				//-----------------------------------------------------
				
					
				//packet Buffers
				data_pk_buffer		= op_prg_list_create();
				data_pk_buffer		= op_prg_mem_alloc (sizeof(List));
				
				rreq_pk_buffer		= op_prg_list_create();
				rreq_pk_buffer		= op_prg_mem_alloc (sizeof(List));
				
				//Packet Common
				ici_list			= op_prg_list_create();
				ici_list			= op_prg_mem_alloc (sizeof(List));
				addr_pk_id_list		= op_prg_list_create();
				addr_pk_id_list		= op_prg_mem_alloc (sizeof(List));
				
				//Acks
				ack_table			= op_prg_list_create();
				ack_table			= op_prg_mem_alloc (sizeof(List));
				
				//Routing Table
				routing_table		= op_prg_list_create();
				routing_table		= op_prg_mem_alloc (sizeof(List));
				
				//Clusters
				stats_cluster_local	= op_prg_list_create();
				stats_cluster_local	= op_prg_mem_alloc (sizeof(List));
				cluster_gw			= op_prg_list_create();					//Cluster for which I am gateway
				cluster_gw			= op_prg_mem_alloc (sizeof(List));	
				cluster_neighbors	= op_prg_list_create();					//I am clusterhead -> The accessible clusters and their gateways
				cluster_neighbors	= op_prg_mem_alloc (sizeof(List));	
				
				if (my_stat_id == 0)
					{
						stats_cluster_global	= op_prg_list_create();
						stats_cluster_global	= op_prg_mem_alloc (sizeof(List));
					}
				
				//----------------------------------------------------
				//
				//			CLUSTER INFO INITIALIZATION
				//
				//-----------------------------------------------------
				
				my_cluster.clusterhead  = -1;
				my_cluster.my_weight	= my_weight();
				
				
				//----------------------------------------------------
				//
				//				INTERRUPTIONS
				//
				//-----------------------------------------------------
				
				//Periodic Updates
				op_intrpt_schedule_self (op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS , PERIODIC_FUNCTIONS_CODE);
				
				//Hellos
				op_intrpt_schedule_call (op_sim_time() + op_dist_uniform(INTERVALL_HELLO) , HELLO_GENERATE_CODE , hello , i);
				
				//Cluster Construction
				op_intrpt_schedule_self (op_sim_time() + 10.0 + op_dist_uniform(INTERVALL_HELLO) , CLUSTER_CONSTRUCTION_CODE);
				
				//Topology Figures
				if(DEBUG_TOPO)
					op_intrpt_schedule_call (op_sim_time() , WRITE_TOPOLOGY_CODE , write_topology_figures , i);
				
				
				
				//Data Transmission
				//For nb_connections nodes, lauch a flow transmission of data packets
				if (NB_CONNECTIONS > current_nb_connections)
					{
						op_intrpt_schedule_self (TIME_BEGIN_DATA + op_dist_uniform(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE);
						current_nb_connections++;
					}
				
				}


			/** state (INIT_AFTER_MAC) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "INIT_AFTER_MAC", "cbrp_process () [INIT_AFTER_MAC exit execs]")
				{
				}


			/** state (INIT_AFTER_MAC) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "INIT_AFTER_MAC", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, state2_enter_exec, "idle", "cbrp_process () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,cbrp_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "idle", "cbrp_process () [idle exit execs]")
				{
				//printf ("%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (ENDSIM)
			FSM_TEST_COND (PERIODIC_FUNCTIONS)
			FSM_TEST_COND (CLUSTER)
			FSM_TEST_COND (PK_DATA_GENERATE)
			FSM_TEST_COND (PK_FROM_LOWER)
			FSM_TEST_COND (UNICAST_RETRANSMISSIONS)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 4, state4_enter_exec, ;, "ENDSIM", "", "idle", "ENDSIM")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "PERIODIC_FUNCTIONS", "", "idle", "PERIODIC_FUNCTIONS")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "CLUSTER", "", "idle", "CLUSTER")
				FSM_CASE_TRANSIT (3, 6, state6_enter_exec, ;, "PK_DATA_GENERATE", "", "idle", "DATA")
				FSM_CASE_TRANSIT (4, 7, state7_enter_exec, ;, "PK_FROM_LOWER", "", "idle", "FROM_LOWER")
				FSM_CASE_TRANSIT (5, 8, state8_enter_exec, ;, "UNICAST_RETRANSMISSIONS", "", "idle", "RET_UNICAST")
				}
				/*---------------------------------------------------------*/



			/** state (PERIODIC_FUNCTIONS) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "PERIODIC_FUNCTIONS", "cbrp_process () [PERIODIC_FUNCTIONS enter execs]")
				{
				//----------------------------------------------------------------
				//				Periodic Functions
				//----------------------------------------------------------------
				
				//Control
				char	filename[50];
				FILE*	file;
				char	tmp[1000];
				int		i;
				
				//For Stats Computing (Clusters)
				int		stats_current_nb_ch;
				
				//Packets common
				void delete_timeout_in_ici_list();
				delete_timeout_in_addr_pk_id_list();
				
				//Routing Table
				delete_timeout_in_routing_table ();
				
				//Cluster Gateways
				delete_timeout_in_cluster_neighbor_gw();
				
				//Packet Buffering
				delete_timeout_in_data_pk_buffer();
					
				//Cluster Topology update
				delete_timeout_in_stats_cluster_global();
				update_stats_cluster_local_list();
				
				
				if (op_sim_time() > TIME_BEGIN_STATS)
					{
				
					 
				//------ STATS Stored in Files -------
				 
						if (my_stat_id+1 == nb_nodes)
							{
							//Periodic stats about network control
								//File Initialization	
								if  (DEBUG_LOAD)
									{
				
										sprintf(filename, "results_cbrp/%d_cbrp_network_control.txt",begin_time);
										file = fopen (filename, "a");
							
										sprintf (tmp, "%f	|", op_sim_time());
										fprintf(file , tmp);
						
										sprintf (tmp, "	%f	|", (double)nb_pk_unicast_ack_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_unicast_ack_instantaneous = 0;
										fprintf(file , tmp);
					
										sprintf (tmp, "	%f	|", (double)nb_pk_hello_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_hello_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_data_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_data_retransmission_instantaneous = 0;
										fprintf(file , tmp);	
				
										sprintf (tmp, "	%f	|", (double)nb_pk_rreq_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_rreq_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_rrep_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_rrep_instantaneous = 0;
										fprintf(file , tmp);	
					
										sprintf (tmp, "	%f	|", (double)nb_pk_rrep_retransmission_instantaneous/(nb_nodes*INTERVALL_PERIODIC_FUNCTIONS));
										nb_pk_rrep_retransmission_instantaneous = 0;
										fprintf(file , tmp);	
					
					
										fprintf(file , "\n");	
										fclose(file);
									}
							}
				
				
				
				//Global Stats
				
					//Degree
						average_degree +=  count_nb_neighbors();
						
					//Clusters
						//Instantaneous Stats
						stats_cluster [my_stat_id].my_clusterhead = my_cluster.clusterhead;
						
						//Final Computing
						if (my_stat_id+1 == nb_nodes)
							{
								//Count the number of current clusterheads
								stats_current_nb_ch = 0;
								for (i=0; i < nb_nodes; i++)
									{
										if (stats_cluster [i].my_clusterhead == stat_id_to_address [i])
											stats_current_nb_ch++;						
									}
								stats_average_nb_of_ch	+= stats_current_nb_ch;
							}
				
				
					}
				
				//Next Stats
				op_intrpt_schedule_self(op_sim_time() + INTERVALL_PERIODIC_FUNCTIONS, PERIODIC_FUNCTIONS_CODE);
				}


			/** state (PERIODIC_FUNCTIONS) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "PERIODIC_FUNCTIONS", "cbrp_process () [PERIODIC_FUNCTIONS exit execs]")
				{
				}


			/** state (PERIODIC_FUNCTIONS) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "PERIODIC_FUNCTIONS", "idle")
				/*---------------------------------------------------------*/



			/** state (ENDSIM) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "ENDSIM", "cbrp_process () [ENDSIM enter execs]")
				{
				//----------------------------------------------------------------
				//				SIMULATION END
				//----------------------------------------------------------------
				
				//Collects some stats when the simulation ends
					//CONTROL
					char	filename[50];
					FILE	*file;
					FILE	*data_file;
					FILE	*rreq_file;
					int 	i , j;
					char	msg[250];
					//AP HELLOS
					double	ap_hellos_rcvd_total				= 0; 
					//AP REG
					int		nb_sent_ap_reg						= 0;
					int		nb_received_ap_reg					= 0;
					int		hops_ap_reg							= 0;
					int		nb_retransmissions_ap_reg			= 0;
					double	delay_ap_reg						= 0;
					//DURATION
					double	stats_time_duration;
					//DATA
					double	delay_data_pk 						= 0;
					int		nb_data_pk_sent						= 0;
					int		nb_data_pk_received					= 0;
					int		throughput_data_pk					= 0;
					int		hops_data_pk						= 0;
					int		nb_retransmissions_data_pk			= 0;
					int		nb_local_repairs_data_pk			= 0;
					double	tmp_distance						= 0;
					int		length_distribution	[MAX_NETWORK_RADIUS];
					//SPEED
				   	double	SPEED_HIGH_MIN 						= 0;
				   	double	SPEED_HIGH_MAX 						= 0;
				   	double	SPEED_LOW_MIN 						= 0;
				   	double	SPEED_LOW_MAX 						= 0;
					int		speed_class							= 0;
					//TOPOLOGY
					double	X_MAX								= 0;
					double	Y_MAX								= 0;
					//RREQ
					int		nb_rreq_sent						= 0;
					int		nb_rreq_received					= 0;
					int		nb_rreq_received_for_ch				= 0;
					int		nb_rreq_received_for_clients		= 0;
					int		nb_ch_during_rreq[MAX_RREQ_PK];
					double	average_nb_ch_during_rreq			= 0;
					int		nb_retry_for_rreq					= 0;
					int		nb_retry_for_success_rreq			= 0;
					//RREP
					int		nb_rrep_sent						= 0;
					int		nb_rrep_received					= 0;
					double	average_delay_for_rrep				= 0;
					double	average_delay_for_rreq_to_final_rrep= 0;
					int		average_nb_retransmissions_rrep 	= 0;
					int		hops_rrep							= 0;
					//RERR
					int		nb_rerr_sent						= 0;
					int		nb_rerr_received					= 0;
					double	average_delay_for_rerr				= 0;
					int		average_nb_retransmissions_rerr 	= 0;
					int		hops_rerr							= 0;
					
				//Stats Per node
					update_stats_cluster_local_list();
					individual_statistics_generate();
				
				//To update Stats about RREQ/RREP/DATA (not already deleted from buffers at the end -> the packet was not and won't be delivered)
					delete_all_in_rreq_pk_buffer();
					
				//Speeds
					if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
						{
							op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &speed_class);
							switch(speed_class)		
								{
									case LOW_SPEED :
										nb_low_speed_nodes++;
									break;
									case HIGH_SPEED :
										nb_high_speed_nodes++;
									break;
								}
						}
				
				
				//Global Stats
					if (my_stat_id+1 == nb_nodes)
						{
							//Initialization
							for (i=0; i< MAX_NETWORK_RADIUS ; i++)
								length_distribution[i] = 0;
				
							//Time Duration for Stats Simualtion
							stats_time_duration = op_sim_time()-TIME_BEGIN_STATS;
							
							//General Parameters
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SPEED_HIGH_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SPEED_HIGH_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SPEED_LOW_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SPEED_LOW_MAX); 
						
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "X_MAX",		&X_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "Y_MAX",		&Y_MAX); 
							
				
							//-------------------
							//       DATA
							//-------------------
							if (DEBUG>0)
								{
									sprintf(filename,"results_cbrp/%d_cbrp_debug_pk_data.txt",begin_time);		
									data_file = fopen(filename , "w");
									fprintf(data_file,"SRC	|	DEST	|	SIZE	|	HOPS	|	RETRY	|NB_REPAIRS	|	GENERATED	|	SENT		|	RECEIVED	|	DELAY		|	DISTANCE	|	ROUTE\n");	
								}
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									nb_data_pk_sent++;
									
									//The packet was received
									if (stats_data_pk [i].time_reception != 0)
										{
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											nb_local_repairs_data_pk 	+= stats_data_pk [i].nb_repairs;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;
											(length_distribution [stats_data_pk [i].hops]) ++;
										}
									
									tmp_distance = sqrt( pow(stats_data_pk [i].src_x_pos - stats_data_pk [i].dest_x_pos , 2) + pow(stats_data_pk [i].src_y_pos - stats_data_pk [i].dest_y_pos , 2));
									if (DEBUG > 0)
										fprintf(data_file,"%d	|	%d	|	%d	|	%d	|	%d	|	%d	|	%f	|	%f	|	%f	|	%f	|	%f	|	%s\n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].pk_size, stats_data_pk[i].hops , stats_data_pk[i].nb_retry , stats_data_pk [i].nb_repairs , stats_data_pk[i].time_generation , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception , stats_data_pk[i].time_reception - stats_data_pk[i].time_emission , tmp_distance , stats_data_pk[i].route);
								}
							if (DEBUG > 0)
								fclose(data_file);
							
							
							//-------------------
							//	ROUTE REQUEST
							//-------------------
							if (DEBUG > 0)
								{
									sprintf(filename,"results_cbrp/%d_cbrp_debug_pk_rreq.txt",begin_time);		
									rreq_file = fopen(filename , "w");
									fprintf(rreq_file,"SRC	|	DEST	|	SENT		|	REC		|	RETRY	|	SENT		|	REC		|	HOPS	|	RETRY\n");
								}
							average_nb_ch_during_rreq = 0;			
							for (i=0 ;  i < stats_nb_rreq ; i++ )
								{
									nb_rreq_sent++;
								
									//Delivery Ratio of Flodding (for RREQ)
									for (j=0; j < nb_nodes ; j++)
										{
											nb_rreq_received_for_clients	+= (stats_rreq [i].rreq_is_rcvd) [j];
											nb_ch_during_rreq[i] = 0;
											if ( (stats_rreq [i].rreq_is_ch)[j] )
												{
													nb_rreq_received_for_ch += (stats_rreq [i].rreq_is_rcvd) [j];
													nb_ch_during_rreq[i]++;
												}
											average_nb_ch_during_rreq += (double) nb_ch_during_rreq[i];
										}
									
									//RREQ successfull
									if ( stats_rreq [i].rreq_time_reception )
										{
											nb_rreq_received ++;
											nb_retry_for_success_rreq	+= stats_rreq [i].rreq_nb_retry + 1;
										}
									
									//Nb of RREQ per route discovering
									nb_retry_for_rreq += stats_rreq [i].rreq_nb_retry + 1;
											
									
							
							//-------------------
							//	ROUTE REPLY
							//-------------------
									//Nb of RREQ that create a RREP
									if (stats_rreq [i].rreq_time_reception != 0)
										nb_rrep_sent++;
				
									if (stats_rreq[i].rrep_time_reception != 0)
										{
											nb_rrep_received++;
											hops_rrep	 					+= stats_rreq [i].rrep_hops;
											average_nb_retransmissions_rrep += stats_rreq [i].rrep_nb_retry;							
											
											//Delays for S(RREQ)->S(RREP) & D(RREP)->S(RREP)
											average_delay_for_rrep 					+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rrep_time_emission;
											average_delay_for_rreq_to_final_rrep 	+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rreq_time_emission;
										}
									if (DEBUG > 0)
										fprintf(rreq_file,"%d	|	%d	|	%f	|	%f	|	%d	|	%f	|	%f	|	%d	|	%d\n", stats_rreq[i].source , stats_rreq[i].dest , stats_rreq[i].rreq_time_emission , stats_rreq[i].rreq_time_reception , stats_rreq[i].rreq_nb_retry , stats_rreq[i].rrep_time_emission , stats_rreq[i].rrep_time_reception , stats_rreq[i].rrep_hops , stats_rreq[i].rrep_nb_retry);
								}
							average_nb_ch_during_rreq = average_nb_ch_during_rreq / nb_rreq_sent;
							if (DEBUG > 0)
								fclose(rreq_file);
				
							//-------------------
							//   ROUTE ERROR
							//------------------
							for (i=0 ;  i < stats_nb_rerr ; i++ )				
								{
									nb_rerr_sent++;
									if (stats_rerr[i].time_reception != 0)
										{
											nb_rerr_received				++;
											average_delay_for_rerr 			+= stats_rerr [i].time_reception - stats_rerr [i].time_emission;
											average_nb_retransmissions_rerr += stats_rerr [i].nb_retry;
											hops_rerr	 					+= stats_rerr [i].hops;
										}
								}		
								
				
							//File Initialization	
							sprintf(filename, "results_cbrp/%d_cbrp_global_stats.txt",begin_time);
							file = fopen (filename, "w");
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, "|                                          Global Statistics for CBRP                                        |\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				   
					
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                           PARAMETERS                                                       |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Nb AP									:	%d\n", 						nb_aps);
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_low_speed_nodes);
							fprintf(file, "X-coordinate max							:	%f\n",						X_MAX);
							fprintf(file, "Y-coordinate max							:	%f\n",						Y_MAX);
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes (i.e. nb of flows)	:	%d\n", 				NB_CONNECTIONS);
							fprintf(file, "Interarrival pk time						:	%f\n", 						INTERARRIVAL_DATA_PK);
							fprintf(file, "Packet Size (in octets)						:	%d\n", 					DATA_PK_SIZE);
							fprintf(file, "Number of packet per flow					:	%d\n", 					NB_PK_PER_FLOW);
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                         DATA                                               |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "TOTAL\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			nb_data_pk_sent );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) nb_data_pk_received / (double)nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk / (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk / nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							fprintf(file, "Average Number of Local Repairs per packet		:	%f\n",		(double) nb_local_repairs_data_pk / nb_data_pk_received );
							fprintf(file, "\n");
							fprintf(file, "--> Route length distribution \n");
							for (i=1; i< MAX_NETWORK_RADIUS ; i++)
								if (length_distribution[i] != 0)
									fprintf(file, "%d hops								:	%d\n",		i , 	length_distribution[i]);					
							fprintf(file, "\n\n");
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                      ROUTE CONTROL                                         |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n------------------------------------------------------- ROUTE REQUEST ---------------------------------------\n");
							fprintf(file, "Nb RREQ Sent							:	%d\n",  				nb_rreq_sent );
							fprintf(file, "Nb packets per RREQ Sent					:	%f\n",  			(double)stats_nb_pk_for_all_rreq / nb_rreq_sent );
							fprintf(file, "Percentage of Successfull RREQ				:	%f\n", 			(double) nb_rrep_sent / nb_rreq_sent );
							fprintf(file, "Average Nb of Clusterheads during all RREQ		:	%f\n",  	average_nb_ch_during_rreq );
							fprintf(file, "Delivery Ratio for Clusterheads				:	%f\n", 			(double) nb_rreq_received_for_ch / (nb_rreq_sent * average_nb_ch_during_rreq ) );
							fprintf(file, "Delivery Ratio for Clients					:	%f\n", 			(double) nb_rreq_received_for_clients / (nb_rreq_sent * nb_nodes) );
							fprintf(file, "End To End Delay 1 RREQ -> 1 RREP				:	%f\n", 		(double) average_delay_for_rreq_to_final_rrep / nb_rrep_received );
							fprintf(file, "Average nb of RREQ for a route discovering		:	%f\n", 		(double) nb_retry_for_rreq / nb_rreq_sent);
							fprintf(file, "Average nb of RREQ for a successfull route discovering:	%f\n", 	(double) nb_retry_for_success_rreq / nb_rreq_received);
							fprintf(file, "\n");
							fprintf(file, "\n------------------------------------------------------- ROUTE REPLY ---------------------------------------\n");
							fprintf(file, "Nb RREP Received							:	%d\n",  			nb_rrep_received );
							fprintf(file, "Percentage of Successfull RREP (over all RREP)		:	%f\n", 	(double) nb_rrep_received / nb_rrep_sent );
							fprintf(file, "Percentage of Successfull RREP (over all RREQ)		:	%f\n", 	(double) nb_rrep_received / stats_nb_rreq );
							fprintf(file, "Average Delay before receiveing the RREP			:	%f\n", 		(double) average_delay_for_rrep / nb_rrep_received );
							fprintf(file, "Average Number of Retransmissions along a RREP		:	%f\n", 	(double) average_nb_retransmissions_rrep / nb_rrep_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rrep / nb_rrep_received  );
							fprintf(file, "\n");
							fprintf(file, "\n------------------------------------------------------- ROUTE ERROR ---------------------------------------\n");
							fprintf(file, "Nb RERR Sent							:	%d\n",  				nb_rerr_sent );
							fprintf(file, "Nb RREP Received							:	%d\n",  			nb_rerr_received );
							fprintf(file, "Percentage of Successfull RERR (over all RERR)		:	%f\n", 	(double) nb_rerr_received / stats_nb_rerr);
							fprintf(file, "Average Delay before receiveing the RREP			:	%f\n", 		(double) average_delay_for_rerr / nb_rerr_received );
							fprintf(file, "Average Number of Retransmissions along a RERR		:	%f\n", 	(double) average_nb_retransmissions_rerr / nb_rerr_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rerr / nb_rerr_received  );
							fprintf(file, "\n\n");
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                         CLUSTER                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "GLOBAL\n");
							fprintf(file, "Average Number Of clusterhead					:	%f\n",		(double) stats_average_nb_of_ch / (op_sim_time()-TIME_BEGIN_STATS) );
							fprintf(file, "\n");
				
							fprintf(file, "CHANGES IN CLUSTERS\n");
							fprintf(file, "Clients which change their clusterhead 			:	%d\n",		         stats_nb_ch_clients_changes );
							fprintf(file, "Clients which change their clusterhead (.s^-1.node-^1):	%f\n",	(double) stats_nb_ch_clients_changes / (nb_nodes*op_sim_time()) );
							fprintf(file, "Clusterhead which become clients				:	%d\n",			         stats_nb_ch_changes );
							fprintf(file, "Clusterhead which become clients (.s^-1.node-^1)	:	%f\n",		(double) stats_nb_ch_changes / (nb_nodes*op_sim_time()) );
							fprintf(file, "\n");
				
							fprintf(file, "TOPOLOGY COMPARISON\n");
							fprintf(file, "Nb of changes of Physic Neighbors				:	%d\n",		         stats_nb_neighbors_changes );
							fprintf(file, "Nb of changes of Physic Neighbors (.s^-1.node-^1)	:	%f\n",	(double) stats_nb_neighbors_changes / (nb_nodes*op_sim_time()) );
							fprintf(file, "Nb of changes of Virtual Neighbors				:	%d\n",	         	 stats_nb_virtual_changes );
							fprintf(file, "Nb of changes of Virtual Neighbors (.s^-1.node-^1)	:	%f\n",	(double) stats_nb_virtual_changes / (nb_nodes*op_sim_time()) );
							fprintf(file, "\n\n");
							
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   Network Control                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
					
							fprintf(file, "--> Average Values per node, per second \n");
							fprintf(file, "Unicast Acks							:	%f\n", 			(double) nb_pk_unicast_ack_total					/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Hellos								:	%f\n", 			(double) nb_pk_hello_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 			(double) nb_pk_data_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 		(double) nb_pk_data_retransmission_total			/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "RREQ									:	%f\n", 			(double) nb_pk_rreq_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "RREP									:	%f\n", 			(double) nb_pk_rrep_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "RREP Retransmissions						:	%f\n", 		(double) nb_pk_rrep_retransmission_total			/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 		(double) (nb_pk_unicast_ack_total + nb_pk_hello_total + nb_pk_data_total + nb_pk_data_retransmission_total + nb_pk_rreq_total + nb_pk_rrep_total + nb_pk_rrep_retransmission_total)/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "\n\n");
							
						}
				
				  
				}


			/** state (ENDSIM) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "ENDSIM", "cbrp_process () [ENDSIM exit execs]")
				{
				}


			/** state (ENDSIM) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "ENDSIM", "idle")
				/*---------------------------------------------------------*/



			/** state (CLUSTER) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "CLUSTER", "cbrp_process () [CLUSTER enter execs]")
				{
				int		clusterhead;
				char	msg[500];
				Boolean	error_timeout , error_hops;
				
				switch (op_intrpt_code())
					{
				//CONSTRUCTION	
					//Elect some nodes which will become clusterheads
						case CLUSTER_CONSTRUCTION_CODE :
							if (is_highest_node())
								become_clusterhead();
							//I have no clusterhead
							else if (my_cluster.clusterhead == -1)
								op_intrpt_schedule_self(op_sim_time() + INTERVALL_HELLO + op_dist_uniform(0.33), CLUSTER_CONSTRUCTION_CODE);
						break;
					
						
						
						
						
						
						
						
						
				//MAINTENANCE	
					//Maintain the structure of clusters	
						case CLUSTER_MAINTENANCE_CODE :
				
							//Maintenance for Clusterheads
							if (my_cluster.clusterhead == my_address)
								{
									//Verify that I am not a useless clusterhead
									if (!is_useless_clusterhead())
										my_cluster.last_time_usefull = op_sim_time();
									
									//If I am useless since a long time, I become client (If I can)
									if (my_cluster.last_time_usefull < op_sim_time() - TIMEOUT_USELESS_CH * INTERVALL_HELLO_CH)
										{							
											//Searches a new clusterhead
											clusterhead = search_a_new_clusterhead();
											
											if (clusterhead!=-1)
												{
													//Debug
													if (DEBUG>1)
														{
															sprintf(msg, "CLUSTER : I am useless Clusterhead since %f, I choose %d as new clusterhead at %f\n", my_cluster.last_time_usefull , clusterhead , op_sim_time());
															cbrp_debug(msg);							
														}
											
													//Takes it
													change_clusterhead (clusterhead);
												}
										}						
								}
						
						
				
							//Maintenance for Clients
							if (my_cluster.clusterhead != my_address)
								{
									//Verify that my clusterhead is already alive, and that it is a 1-Neighbor
									error_hops 		= (hops_routing_entry(my_cluster.clusterhead) != 1);
									error_timeout 	= (timeout_routing_entry(my_cluster.clusterhead) < op_sim_time());
									if (error_hops || error_timeout)
										{
											//Else, try to find another
											print_routing_table();
											clusterhead = search_a_new_clusterhead();
									
											//Debug
											if (DEBUG>1)
												{
													sprintf(msg, "CLUSTER : I lost my clusterhead (timeout=%d, hops=%d), and found %d as new clusterhead at %f\n",error_timeout , error_hops , clusterhead , op_sim_time());
													cbrp_debug(msg);							
												}
									
											//If I found a clusterhead, I take it
											if (clusterhead != -1)
												change_clusterhead (clusterhead);
											//If I have the highest weight and no clusterhead -> I become clusterhead
											else if (is_highest_node())
												become_clusterhead();
											//I must wait the declaration of the highest node of my neighborhood
											else	
												change_clusterhead (-1);
										}
								}
							
							op_intrpt_schedule_self(op_sim_time() + 1.0, CLUSTER_MAINTENANCE_CODE);
						break;
						
						
						
						default :
							op_sim_end("Bad interruption in entering CLUSTER State", "No interruption code corresponds","","");
						break;	
					}
				}


			/** state (CLUSTER) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "CLUSTER", "cbrp_process () [CLUSTER exit execs]")
				{
				}


			/** state (CLUSTER) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "CLUSTER", "idle")
				/*---------------------------------------------------------*/



			/** state (DATA) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "DATA", "cbrp_process () [DATA enter execs]")
				{
				int		dest_final;
				int		i;
				int		network_id;
				int		node_remote_id;
				int		process_remote_id;
				int		its_address;
				
				
				/*------------------------------------------------------------------------------------------	
												   THE FINAL DESTINATION
				-------------------------------------------------------------------------------------------*/					
				//The final destination is random
				dest_final	= op_dist_uniform (nb_nodes-2)+2;
				if (dest_final == my_address)
					dest_final ++;
				//dest_final = 16;
				
				//Identificaiton of the remote localization process
				network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
				node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
				process_remote_id	= op_id_from_name ( node_remote_id, OPC_OBJMTYPE_QPS, PROCESS_ID_NAME);
				
				/*------------------------------------------------------------------------------------------	
											  PACKET GENERATION + TRANSMISSION
				-------------------------------------------------------------------------------------------*/	
				
				for(i=0; i < NB_PK_PER_FLOW ; i++)
					op_intrpt_schedule_call(op_sim_time() + i*INTERARRIVAL_DATA_PK , 0 , send_data , dest_final);
				
				/*------------------------------------------------------------------------------------------	
															NEXT FLOW
				-------------------------------------------------------------------------------------------*/					
				//I must wake up the next source node
				op_intrpt_schedule_remote(op_sim_time() + op_dist_exponential(INTERARRIVAL_DATA_PK*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE , process_remote_id);
				}


			/** state (DATA) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "DATA", "cbrp_process () [DATA exit execs]")
				{
				}


			/** state (DATA) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "DATA", "idle")
				/*---------------------------------------------------------*/



			/** state (FROM_LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "FROM_LOWER", "cbrp_process () [FROM_LOWER enter execs]")
				{
				//Packet Variable
				Packet		*pkptr , *pk_dest;
				Packet		*pk_data;
				int			pk_type;
				
				//Common information in packet
				int			address_dest;
				int			address_dest_final;
				int			address_src;
				int			address_src_init;
				int			address_previous_hop;
				int			pk_id;
				short		ttl;
				short		hops;
				int			id_ap;
				int			next_hop;
				int			clusterhead;
				int			cluster_dest;
				int			stat_id;
				
				//Conditions To handle the packet
				Boolean		is_unicast_for_me;
				Boolean		is_broadcast;
				Boolean		is_ttl_enough;
				Boolean		is_pk_not_seen;
				Boolean		is_bidirect;
				
				//Control
				char		msg[250];
				int			value;
				
				//Delay before packet transmission
				double		delay;
				
				//Fields
				int			field_num;
				char		field_name[20];
				
				/*------------------------------------------------------------------------------------------	
													   INCOMING PACKET 
				-------------------------------------------------------------------------------------------*/					
				
				pkptr = op_pk_get (op_intrpt_strm ());
				op_pk_nfd_get (pkptr, "OPTION_TYPE",&pk_type);
				op_pk_nfd_get (pkptr, "SRC", 		&address_src);
				op_pk_nfd_get (pkptr, "DEST", 		&address_dest);
				op_pk_nfd_get (pkptr, "SRC_INIT", 	&address_src_init);
				op_pk_nfd_get (pkptr, "PK_ID", 		&pk_id);
				op_pk_nfd_get (pkptr, "TTL", 		&ttl);
				
				
				
				
				/*------------------------------------------------------------------------------------------	
													   CONDITIONS FOR PKS 
				-------------------------------------------------------------------------------------------*/					
				is_unicast_for_me 		=	(address_dest == my_address);
				is_broadcast 			=	((address_dest == -1) && (address_src != my_address));
				
				is_ttl_enough 			=	(ttl>0);
				is_pk_not_seen 			=	(addr_pk_id_not_seen(address_src_init , pk_id));
				
				is_bidirect				=	( (is_link_bidirect(address_src)) || (pk_type == HELLO_PK_TYPE) || (pk_type == DATA_PK_TYPE));
				
				
				//Acknowledges the packet if It is unicast and was already seen (The source has not seen my ack/retransmission)
				if (is_unicast_for_me && !is_pk_not_seen)	
					{
						if ((pk_type == DATA_PK_TYPE) && (ACK_FOR_DATA))
							acknowledges_unicast_packet(address_src , pk_id);
						if ((pk_type == RREP_PK_TYPE) && (ACK_FOR_RREP))
							acknowledges_unicast_packet(address_src , pk_id);
						if ((pk_type == RERR_PK_TYPE) && (ACK_FOR_RERR))
							acknowledges_unicast_packet(address_src , pk_id);
					}
				
				//Passive Acknowledgements
				//DATA
				if ((address_src != my_address) && (ACK_FOR_DATA) && (pk_type == DATA_PK_TYPE) && (PROMISCUOUS_FOR_UNICAST))
					delete_unicast_ack(address_src , pk_id);
				//RREP
				if ((address_src != my_address) && (ACK_FOR_RREP) && (pk_type == RREP_PK_TYPE) && (PROMISCUOUS_FOR_UNICAST))
					delete_unicast_ack(address_src , pk_id);
				//RERR
				if ((address_src != my_address) && (ACK_FOR_RERR) && (pk_type == RERR_PK_TYPE) && (PROMISCUOUS_FOR_UNICAST))
					delete_unicast_ack(address_src , pk_id);
				
				
				
				//DEBUG
				if (pk_type == DATA_PK_TYPE)
					{
						sprintf(msg,"%d / %d->%d(id%d-type%d) : %d %d %d %d %d %f\n", my_address , address_src , address_dest , pk_id , pk_type , is_bidirect , is_broadcast , is_unicast_for_me , is_ttl_enough , is_pk_not_seen , op_sim_time());
						cbrp_test(msg);
					}			  
				
				if ( is_bidirect && (is_broadcast || is_unicast_for_me) && is_ttl_enough && is_pk_not_seen )
					{
						
						//Search the type of packet
						switch (pk_type)
							{
								//------------------------------------------	
								//			ACKNOWLEDGEMENTS
								//-------------------------------------------
								case UNICAST_ACK_PK_TYPE:
										//Registers the packet as seen
										add_address_id_couple(address_src , pk_id);
				
										delete_unicast_ack(address_src , pk_id);				
									break;
								
								
								
								
									
								//------------------------------------------	
								//			HELLOS
								//-------------------------------------------
								case HELLO_PK_TYPE:
				
										//Registers the packet as seen
										add_address_id_couple(address_src , pk_id);
				
										//Chooses the source as clusterhead if it is clusterhead ....
										op_pk_nfd_get(pkptr, "CLUSTERHEAD", &clusterhead);
										if ((clusterhead == address_src) && (my_cluster.clusterhead == -1))
											{
												op_intrpt_schedule_self (op_sim_time() + INTERVALL_HELLO, CLUSTER_MAINTENANCE_CODE);
												if (DEBUG>1)
													{
														sprintf(msg, "CLUSTER : I find a new clusterhead (%d), in an hello packet at %f\n",address_src, op_sim_time());
														cbrp_debug(msg);
													}
												change_clusterhead (clusterhead);
											}
								
										//Neighbor Table
										update_neighbors(pkptr);
										
										//For gateways
										//if ((clusterhead !=-1) && (my_cluster.clusterhead != clusterhead) && (my_cluster.clusterhead != -1))
										//	add_cluster_gw (clusterhead);
												
										//STATS : Cluster Topology 
										if ((clusterhead !=-1) && (my_cluster.clusterhead != clusterhead) && (my_cluster.clusterhead != -1))
											add_stats_cluster_global(my_cluster.clusterhead , clusterhead);
									break;
										
										
										
										
									
								//------------------------------------------	
								//			RREQ
								//-------------------------------------------
								case RREQ_PK_TYPE:
									//FOR ALL NODES
										op_pk_nfd_get(pkptr, "DEST_FINAL", 	&address_dest_final);
										op_pk_nfd_get(pkptr, "STAT_ID", 	&stat_id);
				
										//Registers the packet as seen-> Only for CH, the gateways can forward the same CH for different CH
										add_address_id_couple(address_src_init , pk_id);
										
										//Stats
										(stats_rreq[stat_id].rreq_is_rcvd)[my_stat_id] = 1;
										
										//I am the final destination of the RREQ
										if (address_dest_final == my_address)
											{
												add_address_id_couple(address_src_init , pk_id);
												
												//Stats
												stats_rreq	[stat_id].rreq_time_reception 	= op_sim_time();
					
												//Relays (only the last relay, other are not changed)
												add_me_in_relay_fields(pkptr);
												
												//Prepare the pk and send it
												send_rrep(pkptr);
											}
										
												if (DEBUG>1)
													{
														sprintf(msg,"RREQ : %d received the RREQ from %d (%d)\n", my_address , address_src , address_dest);
														cbrp_rreq(msg);
													}
										
									//CLUSTERHEAD
										//Sends it to all cluster-Neighbors (directly or via its gateways)
										if ((my_cluster.clusterhead == my_address) && (address_dest_final != my_address))
											{	
												//Infos
												op_pk_nfd_set(pkptr, "SRC", 	my_address);
												op_pk_nfd_set(pkptr, "TTL",		--ttl);										
												
												//Relay Fields
												add_me_in_relay_fields(pkptr);
												
												//Next Hops
												delay = 0;//0.1 * pow (get_nb_hellos_missed(address_src) , 3);
												set_dest_for_broadcast_pk_for_clusterhead(pkptr , delay);			
												
												//In broadcast for clients
												send_rreq_pk_to_clients(pkptr);
												
												if (DEBUG>1)
													{
														sprintf(msg,"RREQ : CH %d received the RREQ from %d\n", my_address , address_src);
														cbrp_rreq(msg);
													}
											}
								
								
									//CLIENTS
										if ((my_cluster.clusterhead != my_address) && (is_unicast_for_me) && (address_dest_final != my_address))
											{
												//Forward to my clusterhead
												if (address_src != my_cluster.clusterhead)
													{
														op_pk_nfd_set(pkptr, "DEST" , 	my_cluster.clusterhead);
														
														//Common Infos
														op_pk_nfd_set(pkptr, "SRC", 	my_address);
														op_pk_nfd_set(pkptr, "TTL",		--ttl);										
														add_me_in_relay_fields(pkptr);
														
														//Transmission
														if (timeout_routing_entry(address_src) > op_sim_time())
															{
																if (DEBUG>1)
																	{
																		sprintf(msg, "RREQ : %d forwards from %d toward its clusterhead %d\n", my_address , address_src , my_cluster.clusterhead);
																		cbrp_rreq(msg);
																	}
																delay = 0.1 * pow (get_nb_hellos_missed(address_src) , 3);;
																pk_send_delayed (op_pk_copy(pkptr), op_dist_uniform(delay));
															}
														else if (DEBUG > 1)
															{
																sprintf(msg, "RREQ : %d didn't forward a RREQ from %d (timeouted neighbor)\n", my_address , address_src , my_cluster.clusterhead);
																cbrp_rreq(msg);											
															}
															
													}
												//Forward to one member of the required cluster
												else
													{
														//I must examine each entry for which I am gateway in the packet
														field_num = 0;
														sprintf(field_name, "CLUSTER_DEST_%d",field_num);
														while ((field_num <= MAX_CLUSTER_FIELDS_IN_RREQ_PK) && (op_pk_nfd_is_set(pkptr, field_name)))
															{	
																//The Cluster-Destination
																op_pk_nfd_get(pkptr, field_name, &cluster_dest);
				
																//Next Hop
																address_dest = get_relay_toward_cluster(cluster_dest);
																pk_dest = op_pk_copy (pkptr);
																op_pk_nfd_set(pk_dest, "DEST", address_dest);	
																if (DEBUG>1)
																	{
																		sprintf(msg, "RREQ : %d forwards from %d to the cluster %d via the gateway %d\n", my_address , address_src , cluster_dest , address_dest);
																		cbrp_rreq(msg);
																	}
														
																//Common Infos
																op_pk_nfd_set(pk_dest, "SRC", 	my_address);
																op_pk_nfd_set(pk_dest, "TTL",	--ttl);										
																add_me_in_relay_fields(pk_dest);
														
																//Transmission
																if ((address_dest != -1) && (timeout_routing_entry(address_src) > op_sim_time()))
																	{
																		delay = 0.1 * pow (get_nb_hellos_missed(address_src) , 3);														
																		pk_send_delayed (pk_dest, op_dist_uniform(delay));
																	}
																
																//Next field
																sprintf(field_name, "CLUSTER_DEST_%d",++field_num);												
															}
													}
												
											}
				
									break;
										
										
										
										
								
								//------------------------------------------	
								//			RREP
								//-------------------------------------------
								case RREP_PK_TYPE:
										//Acknowledgements
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_RREP) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_src , pk_id);
									
										//Adds as seen
										add_address_id_couple(address_src_init , pk_id);
									
									//FINAL DESTINATION						
										op_pk_nfd_get(pkptr, "RELAY_0", &address_dest_final);
										op_pk_nfd_get(pkptr, "STAT_ID", &stat_id);
										//I verify that no RREP was already received
										if ((address_dest_final == my_address) && (stats_rreq [stat_id].rrep_time_reception == 0) && (stat_id != -1))
											{
												//Saves the route in routing table (source routing)
												op_pk_nfd_get(pkptr, "RELAY_1", &address_previous_hop);
												add_routing_entry(address_src_init, address_previous_hop , MAX_NETWORK_RADIUS-ttl+1, -1 , -1 , op_sim_time()+TIMEOUT_ROUTE, 1 , NULL , create_route_from_rrep(pkptr));
				
												//If stat_id == -1, this is a gratuitous RREP -> We d'ont generate any statistic for this packet
												if (stat_id != -1)
													{
														//Stats
														//RREQ
														stats_rreq	[stat_id].rreq_nb_retry		 = delete_entry_in_rreq_buffer(address_src_init) + 1;	//We send 1 + nb_retry RREQ for a route discovering
														//RREP
														//stats_rreq[stat_id].dest			= my_address;
														stats_rreq 	[stat_id].rrep_hops 		= MAX_NETWORK_RADIUS - ttl + 1;
														if (stats_rreq[stat_id].rrep_time_reception != 0)
															{
																printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
																sprintf(msg, "pb: %d a deja recu un rrep pour cette rreq (previous : %f) at %f!!\n" , my_address , stats_rreq[stat_id].rrep_time_reception , op_sim_time() );
																cbrp_test(msg);
																printf(msg);
															}
														stats_rreq	[stat_id].rrep_time_reception 	= op_sim_time();
													}
													
												
												//data bufferized
												if (!send_data_pk_buffer(address_src_init))
													cbrp_debug("We didn't find any entry for this RREP, the data packet was already sent. It seems to be anormal\n");
												
												if (DEBUG>1)
													{
														sprintf(msg, "!!!!!!!!!!!!  %d received the RREP of %d (relay %d) at %f\n", my_address , address_src_init , address_previous_hop , op_sim_time());
														cbrp_rrep(msg);
													}
											}
				
									
									//CLIENTS
										//I just forward to the next hop in relay fields
										if ((my_cluster.clusterhead != my_address) && (address_dest_final != my_address))
											{
												//Searches the next relay toward the source of RREQ, and sets the "DEST" field
												set_dest_rrep_to_next_relay(pkptr);
												
												op_pk_nfd_set(pkptr, "SRC", my_address);
												op_pk_nfd_set(pkptr, "TTL", --ttl);
																				
												//Info / DEBUG
												op_pk_nfd_get(pkptr, "DEST", 	&address_dest);
												op_pk_nfd_get(pkptr, "RELAY_0", &address_dest_final);
												if (DEBUG>1)
													{	
														sprintf(msg,"%d (client) forwards the RREP from %d to %d toward %d\n",my_address, address_src_init, address_dest , address_dest_final);
														cbrp_rrep(msg);
													}
											
												//Transmission
												if (ACK_FOR_RREP)
													add_unicast_ack(address_dest , pk_id , pkptr);
												pk_send(op_pk_copy(pkptr));									
											}
									
									
									
									//CLUSTERHEADS
										if ((my_cluster.clusterhead == my_address) && (address_dest_final != my_address))
											{
												//Searches the next relay toward the source of RREQ, and sets the "DEST" field
												set_dest_rrep_to_next_relay(pkptr);
												
												//Bypass me in Relay Fields If I am useless
												bypass_me_if_useless_in_rrep(pkptr);								
												op_pk_nfd_set(pkptr, "SRC", my_address);
												op_pk_nfd_set(pkptr, "TTL", --ttl);
												
												if (DEBUG>1)
													{	
														op_pk_nfd_get(pkptr, "DEST", 	&address_dest);
														op_pk_nfd_get(pkptr, "RELAY_0", &address_dest_final);
														sprintf(msg,"%d (CH) forwards the RREP from %d to %d toward %d\n",my_address, address_src_init, address_dest , address_dest_final);
														cbrp_rrep(msg);
													}
											
												//Transmission
												if (ACK_FOR_RREP)
													add_unicast_ack(address_dest , pk_id , pkptr);
												pk_send(op_pk_copy(pkptr));
											}
									
									break;
										
										
										
										
										
										
								//------------------------------------------	
								//			DATA
								//-------------------------------------------
								case DATA_PK_TYPE:
										//Ack
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_DATA) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_src , pk_id);
				
										//Registers the packet as seen
										add_address_id_couple(address_src_init , pk_id);
									
										//Final Destination
										op_pk_nfd_get(pkptr, "DEST_FINAL", 	&address_dest_final);
										op_pk_nfd_get(pkptr, "STAT_ID", 	&stat_id);
									
										//Adds my id as forwarder
										if (strlen(stats_data_pk [stat_id].route) < 45)
											sprintf(stats_data_pk [stat_id].route, "%s | %d ", stats_data_pk [stat_id].route , my_address);
									
									//FINAL DESTINATION
										if (address_dest_final == my_address)
											{
												//Ack
												if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_DATA) && (PROMISCUOUS_FOR_UNICAST))	
													acknowledges_unicast_packet(address_src , pk_id);
												
												//Stats
												stats_data_pk 	[stat_id].time_reception	= op_sim_time();
												stats_data_pk	[stat_id].dest				= my_address;
												stats_data_pk	[stat_id].pk_size			= (int) op_pk_bulk_size_get(pkptr);
												stats_data_pk	[stat_id].hops				= MAX_NETWORK_RADIUS - ttl + 1;
												op_pk_nfd_get(pkptr, "NB_REPAIRS", &(stats_data_pk[stat_id].nb_repairs));
												op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stat_id].dest_x_pos));	
												op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stat_id].dest_y_pos));	
												
												//Debug
												if (DEBUG>1)
													{
														sprintf(msg,"-------- DATA received by %d at %f (pk_id %d and stat_id %d) (nb hops=%d) --------\n" , my_address , op_sim_time() , pk_id , stat_id , MAX_NETWORK_RADIUS - ttl + 1);
														cbrp_data(msg);
														sprintf(msg, "DATA - Reception from %d (src_init %d, pk_id=%d) at %f\n", address_src , address_src_init , stat_id , op_sim_time());
														cbrp_debug(msg);
													}
											}
									
									//RELAY
										if ((ttl>1) && (address_dest_final != my_address))
											{
												//Next Relay
												next_hop = set_dest_data_to_next_relay(pkptr);
												
												//If the next hop is not a 1-neighbor, try to find a new relay (if not found -> sends a Route Error)
												if ((is_bidirect_neighbor(next_hop)) || (handle_route_error_for_data(pkptr , &next_hop)))
													{		
														//Info
														op_pk_nfd_set(pkptr, "SRC", my_address);
														op_pk_nfd_set(pkptr, "TTL", --ttl);
												
														//DEBUG
														if (DEBUG>1)
															{
																sprintf(msg, "->DATA - relay from %d to %d  (src_init %d and toward %d) at %f\n", my_address , next_hop , address_src_init , address_dest_final , op_sim_time());
																cbrp_data(msg);
															}
											
														//Transmission
														if (ACK_FOR_DATA)
															add_unicast_ack(next_hop , pk_id , pkptr);
														pk_send_delayed(op_pk_copy(pkptr) , 0);
													}
											}
										
									break;
								//------------------------------------------	
								//			ROUTE ERRORS
								//-------------------------------------------
								case RERR_PK_TYPE:
										//Ack
										if ((MAX_NB_RETRIES_UNICAST_ACKS != 0) && (ACK_FOR_RERR) && (!PROMISCUOUS_FOR_UNICAST))
											acknowledges_unicast_packet(address_src , pk_id);
				
										//Registers the packet as seen
										add_address_id_couple(address_src_init , pk_id);
									
										//Final Destination
										op_pk_nfd_get(pkptr, "DEST_FINAL", 	&address_dest_final);
										op_pk_nfd_get(pkptr, "STAT_ID", 	&stat_id);
									
									//FINAL DESTINATION
										if (address_dest_final == my_address)
											{
												//Ack
												acknowledges_unicast_packet(address_src , pk_id);								
							
												//Debug
												if (DEBUG>1)
													{
														sprintf(msg,"-------- DATA : RERR received by %d at %f (pk_id %d and stat_id %d) (nb hops=%d) --------\n" , my_address , op_sim_time() , pk_id , stat_id , MAX_NETWORK_RADIUS - ttl + 1);
														cbrp_data(msg);
														cbrp_rerr(msg);
														sprintf(msg, "RERR - Reception from %d (src_init %d, pk_id=%d) at %f\n", address_src , address_src_init , stat_id , op_sim_time());
														cbrp_debug(msg);
													}
												
												//Delete the obsolete route
												delete_route(get_last_relay(pkptr));
												
												//Stats
												stats_rerr 	[stat_id].time_reception	= op_sim_time();
												stats_rerr	[stat_id].dest				= my_address;
												stats_rerr	[stat_id].hops				= MAX_NETWORK_RADIUS - ttl + 1;
											}
									
									//RELAY
										if ((ttl>1) && (address_dest_final != my_address))
											{
				
												//Searches the next relay toward the source of RREQ, and sets the "DEST" field
												set_dest_rrep_to_next_relay(pkptr);
												
												op_pk_nfd_set(pkptr, "SRC", my_address);
												op_pk_nfd_set(pkptr, "TTL", --ttl);
																				
												//Info / DEBUG
												op_pk_nfd_get(pkptr, "DEST", 	&address_dest);
												op_pk_nfd_get(pkptr, "RELAY_0", &address_dest_final);
												
												if (DEBUG>1)
													{	
														sprintf(msg,"-> RERR relay in %d from %d to %d (src_init %d and toward %d) at %f\n", my_address , address_src , address_dest , address_src_init , address_dest_final, op_sim_time());
														cbrp_data(msg);
														cbrp_rerr(msg);
													}
											
												//Transmission
												if (ACK_FOR_RREP)
													add_unicast_ack(address_dest , pk_id , pkptr);
												pk_send(op_pk_copy(pkptr));
											}
										
										break;
									
								default :
										sprintf(msg, "PK TYPE = %d", pk_type);
										op_sim_end("pk type not known !! in PK_FROM_LOWER", msg, "","");
									break;
				
							}
					}
					
					
					
					
				//The pk was already trated, we destroy it to free memory
				op_pk_destroy(pkptr);
				}


			/** state (FROM_LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "FROM_LOWER", "cbrp_process () [FROM_LOWER exit execs]")
				{
				}


			/** state (FROM_LOWER) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "FROM_LOWER", "idle")
				/*---------------------------------------------------------*/



			/** state (RET_UNICAST) enter executives **/
			FSM_STATE_ENTER_FORCED (8, state8_enter_exec, "RET_UNICAST", "cbrp_process () [RET_UNICAST enter execs]")
				{
				//retransmissions of all not acknowldged entries
					struct_ack*		couple;
					//Control
					char			msg [200];
					int				i;
					double			older_entry;
					//Random delay before transmitting
					double			delay;
					//Info for/from the packet
					Packet*			pk_dest;
					int				address_final;
					int				address_src_init;
					int				stat_id;
					int				pk_type;
					int				pk_id;
					int				next_hop;
				
				
					//Older entry variable contains the time for which we must schedule an interuption
					older_entry = -1;
				
				//If the ack table is empty, we don't treat it ....
					if (op_prg_list_size(ack_table)!=0)
						{
							//For each entry
							for (i=op_prg_list_size(ack_table)-1 ; i>=0 ; i--)
								{
									//gets the entry
									couple = (struct_ack*) op_prg_list_access (ack_table, i);
									
									//Get packet type
									op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
									op_pk_nfd_get(couple->pkptr, "PK_ID", 		&pk_id);
									op_pk_nfd_get(couple->pkptr, "DEST_FINAL",	&address_final);
							
									//Verifies each entry
									if (couple->timeout <= op_sim_time())
										{
											//Test for max nb retransmissions
											if (couple->nb_retry >= MAX_NB_RETRIES_UNICAST_ACKS)
												{
													//If this a data packe, try another a local repair
													if ((pk_type == DATA_PK_TYPE) && (couple->nb_repairs < MAX_NB_REPAIRS_FOR_ONE_NODE))
														{
															next_hop = set_dest_data_to_next_relay(couple->pkptr);
															if (handle_route_error_for_data(couple->pkptr , &next_hop))
																{										
																	//DEBUG
																	if (DEBUG>1)
																		{
																			sprintf(msg, "->DATA - relay from %d to %d  (src_init %d and toward %d) at %f (After %d retransmissions)\n", my_address , next_hop , address_src_init , address_final , op_sim_time() , couple->nb_retry);
																			cbrp_data(msg);
																		}
																	
																	//Info Initialization
																	couple->dest 		= next_hop;
																	couple->nb_retry	= 0;
																	couple->nb_repairs++;
																	
																	//Transmission
																	//if (ACK_FOR_DATA)
																	//	add_unicast_ack(next_hop , pk_id , couple->pkptr , );
																	pk_send_delayed(op_pk_copy(couple->pkptr) , op_dist_uniform(0.001));										
																}
															//We generated a Route Error, we just drop the data pk in acks
															else
																{
																	op_prg_list_remove (ack_table , i);
																	free(couple);
																}
														}
													//Remove it in the retransmission list	
													else
														{
															op_prg_list_remove (ack_table , i);
															free(couple);
														}
				
												}
										
											if (couple->nb_retry < MAX_NB_RETRIES_UNICAST_ACKS)
												{
													op_pk_nfd_get(couple->pkptr, "STAT_ID",&stat_id);
				
													//Stats of nb of retransmissions
													switch (pk_type)
														{
															case DATA_PK_TYPE :
																stats_data_pk [stat_id].nb_retry++;
																if (DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		cbrp_data (msg);
																	}
															break;
															case RREP_PK_TYPE :
																if (DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		cbrp_rrep (msg);
																	}
															break;
															case RERR_PK_TYPE :
																stats_rerr [stat_id].nb_retry++;
																if (DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		cbrp_rerr (msg);
																	}
															break;
														}
															
												
													//retransmission
													couple->timeout = op_sim_time() + TIMEOUT_UNICAST_ACK;
													couple->nb_retry++;	
													delay = op_dist_uniform(0.005);
													pk_retransmit_delayed (op_pk_copy(couple->pkptr) , delay);			
														
													//DEBUG
													if (DEBUG>1)
														{
															sprintf(msg, "RETRANSMISSION : we retransmit packet to %d with pk_id %d and currently %d retransmissions at %f\n", couple->dest , couple->pk_id , couple->nb_retry+1 , op_sim_time()+delay);
															cbrp_debug (msg);
														}							
												}
				
										}
									if ((couple->timeout < older_entry) || (older_entry==-1))
										older_entry = couple->timeout;
								}
				
				
							//The next verification
							if (older_entry != -1)
								op_intrpt_schedule_self (older_entry , UNICAST_RETRANSMISSIONS_CODE);
						}
				
				
				}


			/** state (RET_UNICAST) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "RET_UNICAST", "cbrp_process () [RET_UNICAST exit execs]")
				{
				}


			/** state (RET_UNICAST) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "RET_UNICAST", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,cbrp_process)
		}
	}

#if defined (__cplusplus)
	extern "C" { 
#endif
	extern VosT_Fun_Status Vos_Catmem_Register (const char * , int , VosT_Void_Null_Proc, VosT_Address *);
	extern VosT_Address Vos_Catmem_Alloc (VosT_Address, size_t);
	extern VosT_Fun_Status Vos_Catmem_Dealloc (VosT_Address);
#if defined (__cplusplus)
	}
#endif


Compcode
cbrp_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (cbrp_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (cbrp_process)",
			sizeof (cbrp_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
			{
			FRET (OPC_COMPCODE_FAILURE)
			}
		}

	*gen_state_pptr = Vos_Catmem_Alloc (obtype, 1);
	if (*gen_state_pptr == OPC_NIL)
		{
		FRET (OPC_COMPCODE_FAILURE)
		}
	else
		{
		/* Initialize FSM handling */
		((cbrp_process_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
cbrp_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
cbrp_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (cbrp_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in cbrp_process_svar function. */
#undef my_address
#undef DEBUG
#undef current_id
#undef my_stat_id
#undef addr_pk_id_list
#undef routing_table
#undef ack_table
#undef distrib
#undef DEBUG_DATA
#undef DEBUG_LOAD
#undef my_cluster
#undef stats_cluster_local
#undef cluster_gw
#undef cluster_neighbors
#undef ici_list
#undef DEBUG_CONTROL
#undef DEBUG_TOPO
#undef data_pk_buffer
#undef rreq_pk_buffer
#undef NB_CONNECTIONS
#undef DATA_PK_SIZE
#undef NB_PK_PER_FLOW
#undef INTERARRIVAL_DATA_PK
#undef is_AP
#undef ACK_FOR_DATA



void
cbrp_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	cbrp_process_state		*prs_ptr;

	FIN (cbrp_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (cbrp_process_state *)gen_ptr;

	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("DEBUG" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG);
		FOUT;
		}
	if (strcmp ("current_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_id);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("addr_pk_id_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->addr_pk_id_list);
		FOUT;
		}
	if (strcmp ("routing_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->routing_table);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("distrib" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->distrib);
		FOUT;
		}
	if (strcmp ("DEBUG_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_DATA);
		FOUT;
		}
	if (strcmp ("DEBUG_LOAD" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_LOAD);
		FOUT;
		}
	if (strcmp ("my_cluster" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_cluster);
		FOUT;
		}
	if (strcmp ("stats_cluster_local" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->stats_cluster_local);
		FOUT;
		}
	if (strcmp ("cluster_gw" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cluster_gw);
		FOUT;
		}
	if (strcmp ("cluster_neighbors" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cluster_neighbors);
		FOUT;
		}
	if (strcmp ("ici_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ici_list);
		FOUT;
		}
	if (strcmp ("DEBUG_CONTROL" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_CONTROL);
		FOUT;
		}
	if (strcmp ("DEBUG_TOPO" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG_TOPO);
		FOUT;
		}
	if (strcmp ("data_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->data_pk_buffer);
		FOUT;
		}
	if (strcmp ("rreq_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->rreq_pk_buffer);
		FOUT;
		}
	if (strcmp ("NB_CONNECTIONS" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_CONNECTIONS);
		FOUT;
		}
	if (strcmp ("DATA_PK_SIZE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DATA_PK_SIZE);
		FOUT;
		}
	if (strcmp ("NB_PK_PER_FLOW" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_PK_PER_FLOW);
		FOUT;
		}
	if (strcmp ("INTERARRIVAL_DATA_PK" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->INTERARRIVAL_DATA_PK);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("ACK_FOR_DATA" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ACK_FOR_DATA);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

