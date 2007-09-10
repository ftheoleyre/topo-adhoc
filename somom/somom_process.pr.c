/* Process model C form file: somom_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char somom_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 43ED13A2 43ED13A2 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
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
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>
#include	"../cdcl/cdcl_biblio.h"


/*----------------------------------------------------------------------
						CONSTANTS			
----------------------------------------------------------------------*/



// COMMON
#define		SOMOM_LOW_SPEED					1
#define		SOMOM_HIGH_SPEED				2


// STREAMS
#define		STRM_FROM_LOWER		   			0
#define		STRM_TO_LOWER					0

// DATA
#define		INTERVALL_DATA_PK_AP			2.0
#define		INTERARRIVAL_DATA_PK			0.25
#define		NB_PK_PER_FLOW					8
#define		DATA_PK_UPLOAD_RATIO			1

//Max nb of pk for stats
#define		MAX_DATA_PK						1000000

// RREQ
#define		TIMEOUT_RREQ_PK_BUFFER			0.1
#define		MAX_NB_RREQ_RETRY				3

// ACKS
#define		MAX_NB_RETRIES_UNICAST_ACKS		3
#define		ACK_FOR_DATA					1
#define		ACK_FOR_RREP					1
#define		ACK_FOR_RUP						0
#define		ACK_FOR_RDEL					0

//TIMEOUTS
#define		TIMEOUT_UNICAST_ACK				0.2			//Acks in Unicast
#define		TIMEOUT_DATA_PK_BUFFER			0.5
#define		TIMEOUT_COMMUNICATION			2.0
#define 	TIMEOUT_ROUTE_UPDATE			2.2			//Maximum Time Between 2 SEND_UPDATE

//Paging
#define		TIMEOUT_PAGING_BUFFER			0.5
#define		INTERVALL_PAGING_REP			2
#define		TIMEOUT_PAGING_ROUTING_TABLE	3.2			//*INTERVALL_PAGING_REP
#define		MAX_NB_NODES_IN_PAGING_REP		70			//1->70

//Route Management
#define 	TIMEOUT_LOCALIZATION			15.0		// definition of the delay of validity of a route in localization table
#define		MAX_NB_NODES_IN_RDEL			20


// Constant used to determine the beginning of the address field in the route delete packet 
#define 	ADDRESS_FIELD					8


// constant used to determine which field of the time_table we have to fill in the update_time_table function
#define		CREATED							1
#define		SENT							2
#define		RECEIVED						3



//----------------------------------------------------------------------
//						Interruptions			
//----------------------------------------------------------------------

//CODES
#define		ROUTE_EXPIRED_CODE				101
#define	   	TIMER_RRREP_EXPIRED_CODE		102
#define 	RREQ_RETRY_CODE					103
#define		RREQ_VERIFY_CODE				104

#define		SEND_UPDATE_CODE				110

#define		PK_DATA_GENERATE_CODE			120
#define		UNICAST_RETRANSMISSIONS_CODE	121


//INTERRUPTIONS
#define		TEST_INTERRUPTION			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == TEST)
#define		STATE_CHANGED				(op_intrpt_type() == OPC_INTRPT_REMOTE) && (op_intrpt_code() == STATE_CHANGE_CODE)

#define		PK_FROM_HIGHER				(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_HIGHER)
#define		PK_FROM_LOWER				(op_intrpt_type() == OPC_INTRPT_STRM  ) && (op_intrpt_strm() == STRM_FROM_LOWER)

#define		WAIT_STATE_END				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == WAIT_STATE_CODE)
#define		ROUTE_EXPIRED				(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == ROUTE_EXPIRED_CODE)
#define		SON_LOST					(op_intrpt_type() == OPC_INTRPT_REMOTE) && (op_intrpt_code() == SON_LOST_CODE)
#define 	TIMER_ROUTE_REPLY_EXPIRED 	(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == TIMER_ROUTE_REPLY_EXPIRED_CODE)
#define		DIE							(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == DIE_CODE)
#define		ROUTE_REQUEST_RETRY			(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == ROUTE_REQUEST_RETRY_CODE)
#define		SEND_UPDATE					(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == SEND_UPDATE_CODE)

#define		PK_DATA_GENERATE	    	(op_intrpt_code() == PK_DATA_GENERATE_CODE)
#define		UNICAST_RETRANSMISSIONS		(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == UNICAST_RETRANSMISSIONS_CODE)
#define		RREQ_VERIFY					(op_intrpt_type() == OPC_INTRPT_SELF  ) && (op_intrpt_code() == RREQ_VERIFY_CODE)

#define		ENDSIM							(op_intrpt_type() == OPC_INTRPT_ENDSIM)




//----------------------------------------------------------------------
//				     		Structures
//----------------------------------------------------------------------


//-------- PK COMMON MANAGEMENT ---------

//For Addr/pk_id records
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
	packet*		pkptr;	
} ack_couple;

   
//For the Destination of Data Packets
typedef struct {
	short		count;
	int			addr;
} struct_dest;




//-------- PK COMMON MANAGEMENT ---------
typedef struct{
	double		last_time_update;
	double		last_time_useful;
	Boolean		is_important;
} struct_communicating;




//-------- LOCALIZATION ---------

//For the localization table
typedef struct {
	int 	address;
	int		relay;
	double	timeout;
	short 	packet_id; //id of the last packet received which updated the table

	struct loc_cell *next;
} loc_cell;




//-------- LOCALIZATION-PAGING ---------

//For the localization table
typedef struct {
	int 	dest;
	int		ap;
	short	hops;
	double	timeout;
} struct_paging;




//-------- BUFFER ---------

//Data Pk Buffer
typedef struct{
	Packet	*packet;
	int		dest;
	double	timeout;
} struct_pk_buffer;


//RREQ Buffer
typedef struct{
	int		dest;
	double	timeout;
	short	nb_retry;
	int		stat_id;
	packet*	pkptr;	
} struct_rreq_pk_buffer;




//-------- STATS ---------



// table which contains the number of route-request sent for each destination
typedef struct {
	int node_address;
	int number_of_try;
	int response_received;
	int count_route_request;
	struct table_try_route_request *next;
} table_try_route_request;


// table uses to calculate the delivery_delay of data_pk
typedef struct {
	int		pk_id;
	int 	src;
	int 	dest;
	Boolean	pk_local;
	double 	time_created;
	double	time_sent;
	double	time_received;
	
	struct 	time_pk_table* next;

} time_pk_table;

typedef struct {
	int pk_id;	
	int	src;
	int	dest;
	double time; // time of the creation or the reception
	
	struct	stat_table* next;
} stat_table;



//----------------------------------------------------------------------
//						Structures For Stats Collect
//----------------------------------------------------------------------


//DATA PK
typedef struct{
	int		source;
	int		dest;
	int		pk_size;
	short	hops;
	short	nb_retry;
	double	time_generation;
	double	time_emission;
	double	time_reception;
} struct_stats_data;


//RREQ/RREP PK
typedef struct{
	int			source;
	int			dest;
	double		rreq_time_emission;
	double		rreq_time_reception;
	int			rreq_nb_retry;
	double		rrep_time_emission;
	double		rrep_time_reception;
	int			rrep_hops;
	int			rrep_nb_retry;
} struct_stats_rreq;





//----------------------------------------------------------------------
//				     		STATS
//----------------------------------------------------------------------
//Common

int			nb_nodes = 0;
int			current_nb_sleeping_nodes_allowed	= 0;
double		ratio_of_sleeping_nodes				= 0;
int			begin_name_stats = 0;
int			_somom_nb_aps=0;

//Stats Id
int			stat_id_to_address 	[MAX_NB_NODES];									//NB : the first node has stat_id=0
int			address_to_stat_id 	[MAX_ADDRESS];

//Energy
double		somom_sleeping_total	= 0;

//Seed
int seed=0;


//----------- Global Variables ---------
int		time_name_stats = 0;
int		is_paging_activated = 0;	//Is the paging mode activated (The paging master initiates the connections, generates the data, handles the paging ...)




//----------------------------------------------------------------------
//						    Data 	Packets		
//----------------------------------------------------------------------
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;
int			stats_nb_data_pk_down	= 0;
int			stats_nb_data_pk_up		= 0;





//----------------------------------------------------------------------
//					    RREQ / RREP 	Packets		
//----------------------------------------------------------------------
struct_stats_rreq	stats_rreq 	[MAX_DATA_PK];

int			stats_nb_rreq 				= 0;
int			stats_nb_pk_for_all_rreq 	= 0;
int			stats_nb_pk_for_all_rrep 	= 0;




//----------------------------------------------------------------------
//					    FLOWS	
//----------------------------------------------------------------------
int 		nb_pk_somom_data_instantaneous					= 0;
int			nb_pk_somom_data_total							= 0;
int			nb_pk_somom_data_retransmission_instantaneous	= 0;
int			nb_pk_somom_data_retransmission_total			= 0;

int 		nb_pk_somom_rreq_instantaneous					= 0;
int			nb_pk_somom_rreq_total							= 0;

int 		nb_pk_somom_rrep_instantaneous					= 0;
int			nb_pk_somom_rrep_total							= 0;
int			nb_pk_somom_rrep_retransmission_instantaneous	= 0;
int			nb_pk_somom_rrep_retransmission_total			= 0;

int 		nb_pk_somom_rup_instantaneous					= 0;
int			nb_pk_somom_rup_total							= 0;

int 		nb_pk_somom_rdel_instantaneous					= 0;
int			nb_pk_somom_rdel_total							= 0;

int 		nb_pk_somom_ack_instantaneous					= 0;
int			nb_pk_somom_ack_total							= 0;




//----------------------------------------------------------------------
//			    	Pairs SOURCE/DEST MANAGEMENT	
//----------------------------------------------------------------------

short	actual_nb_connections 		= 0;



int		nb_somom_low_speed_nodes 	= 0;
int		nb_somom_high_speed_nodes 	= 0;





//----------------------------------------------------------------------
//				     		FUNCTIONS
//----------------------------------------------------------------------
//ROUTING
int 	get_relay_to_neigbour_node(int);
int 	get_relay_to_internet();
int 	get_relay_to_node(int,Boolean);
void 	send_to_sons(Packet *);

//DATA
void 	send_data_pk(Packet* pk);
Boolean send_data_pk_buffer(int destination , int hops);
void 	delete_timeout_in_data_pk_buffer();
void 	add_in_data_pk_buffer(Packet *pk_dest);

// ACKS
void 	add_unicast_ack(int dest , int pk_id , Packet* pkptr);
void 	delete_unicast_ack(int dest , int pk_id);
void 	acknowledges_unicast_packet(int address , int pk_id);

//LOCALIZATION
int 	delete_localization_entry(int addr);
void 	update_localization_table(int addr_src, int addr_relay);
void 	delete_old_entry(Packet *pk);

//RREQ
void 	send_rreq_pk(int addr , int stat_id);
void 	send_route_request(int addr);
void 	forward_route_request(Packet* pkptr);
void 	send_route_reply(int addr , int stat_id);

// ROUTE UPDATE/DELETE
Boolean create_route_delete(Packet*,int);
void 	send_route_update();

//DEBUG
void 	print_unicast_ack_table();

void 	write_final_stats();
void 	write_node_stat();
void 	write_sons();
void 	write_dominatees();
void 	display_localization_table(void);
void 	node_debug(char*);

void	rrep_debug(char* msg);
void	rreq_debug(char* msg);
void	rdel_debug(char* msg);
void	rup_debug(char* msg);
void	data_debug(char* msg);
void	ack_debug(char* msg);
void	common_debug(char* msg);
void 	paging_debug(char* message);

// COMMON
void 	update_time_table(int,Packet *,Boolean);
time_pk_table *time_table;	//table which contains the time to calculate delivery_delay

// NETWORK
void 	somom_pk_send_delayed(Packet* pkptr , double delay);
void 	somom_pk_send (Packet* pkptr);
void 	somom_pk_retransmit_delayed(Packet* pkptr , double delay);
void 	somom_pk_retransmit (Packet* pkptr);

// PAGING
void 	empty_paging_buffer(int dest , int ap);
void 	send_paging_rep(int dest_final , short hops);
void 	send_paging_ack(Packet* pk_data , int ap_dest);
void 	send_paging_req(int dest_final);
void 	delete_timeout_in_paging_routing_table(int code, int unused);
void 	add_paging_pk(Packet* pk_src);
void 	add_in_paging_routing_table(int dest , int ap , short hops);
int		get_ap_for_dest_in_paging_routing_table(int dest);
void 	print_paging_buffer();



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
	neigh_cell*	            		neighbour_table;
	cds*	                   		my_cds;
	int	                    		is_AP;
	loc_cell*	              		localization_table;
	List*	                  		data_pk_buffer;
	int	                    		my_address;
	stat_table*	            		received_stat_table;
	stat_table*	            		sent_stat_table;
	int	                    		my_stat_id;
	List*	                  		ack_table;
	Boolean	                		DEBUG;
	List*	                  		rreq_pk_buffer;
	int	                    		current_id;
	short	                  		nb_connections;
	double	                 		intern_com_ratio;
	int	                    		data_pk_size;
	struct_communicating	   		communication_info;
	int	                    		cdcl_process_id;
	List*	                  		paging_buffer;
	List*	                  		paging_routing_table;
	Boolean	                		is_paging_master;
	Boolean	                		is_sleeping_authorized;
	} somom_process_state;

#define pr_state_ptr            		((somom_process_state*) SimI_Mod_State_Ptr)
#define neighbour_table         		pr_state_ptr->neighbour_table
#define my_cds                  		pr_state_ptr->my_cds
#define is_AP                   		pr_state_ptr->is_AP
#define localization_table      		pr_state_ptr->localization_table
#define data_pk_buffer          		pr_state_ptr->data_pk_buffer
#define my_address              		pr_state_ptr->my_address
#define received_stat_table     		pr_state_ptr->received_stat_table
#define sent_stat_table         		pr_state_ptr->sent_stat_table
#define my_stat_id              		pr_state_ptr->my_stat_id
#define ack_table               		pr_state_ptr->ack_table
#define DEBUG                   		pr_state_ptr->DEBUG
#define rreq_pk_buffer          		pr_state_ptr->rreq_pk_buffer
#define current_id              		pr_state_ptr->current_id
#define nb_connections          		pr_state_ptr->nb_connections
#define intern_com_ratio        		pr_state_ptr->intern_com_ratio
#define data_pk_size            		pr_state_ptr->data_pk_size
#define communication_info      		pr_state_ptr->communication_info
#define cdcl_process_id         		pr_state_ptr->cdcl_process_id
#define paging_buffer           		pr_state_ptr->paging_buffer
#define paging_routing_table    		pr_state_ptr->paging_routing_table
#define is_paging_master        		pr_state_ptr->is_paging_master
#define is_sleeping_authorized  		pr_state_ptr->is_sleeping_authorized

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	somom_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                  ROUTING
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//Is the destination my dominatee or disconnected neighbor ? I must act as proxy for the RREQ
Boolean must_rreq_proxy(int addr){
	neigh_cell *ptr;
	ptr= neighbour_table;

	while ( ptr != NULL)
		{
			if ((ptr->address == addr) && (ptr->bidirect))
				{	
					if ((ptr->state != DOMINATOR) && ((ptr->father == my_address) || (ptr->father == 0) || (ptr->father == -1)))
						return (OPC_TRUE);
					else	
						return (OPC_FALSE);
				 }
			else
				ptr = (neigh_cell *)ptr->next;
		 }

	return (OPC_FALSE);
}

//Next hop toward one of our k_cds-neighbor
int get_relay_to_neigbour_node(int addr){
	neigh_cell *ptr;
	ptr= neighbour_table;
	while ( ptr != NULL)
		{
			if ((ptr->address == addr) && (ptr->bidirect) && (!ptr->sleep))
				return ptr->relay;

			//next Cell
			ptr = (neigh_cell *)ptr->next;
		 }
	return (-1);
}

//Next hop toward the AP
int get_relay_to_internet(){
	int		next_hop = -1;

	//If I am dominatee, forward to my relay to dominator / or my dominator		
	if (my_cds->state == DOMINATEE)
		{
			//Tries to forward directly toward my ap via my neighborhood (avoid loops in backbone, and a bottleneck near the AP)
			if (my_cds->id_ap > 0)
				next_hop = get_relay_to_neigbour_node(my_cds->id_ap);
			if (next_hop != -1)
				return(next_hop);
			else	
				return(get_relay_to_neigbour_node(my_cds->father));
		}
	
	//If I am dominator, forwards to my father			
	if (my_cds->state == DOMINATOR)
		return(my_cds->father);	
}

	
//Next hop toward an entry in the localization table
int get_relay_to_node_from_localization(int addr, Boolean update){
	loc_cell *ptr;
	ptr= localization_table;

	if (addr == ADDR_MULTICAST_AP)
		return (get_relay_to_internet());
	
	while ( ptr != NULL)
		{
					if((ptr->address)==addr)
						{
							if(ptr->timeout<op_sim_time())
								{									
									delete_localization_entry(addr);
									return -1;
								}
							if(update==OPC_TRUE)
								ptr->timeout= op_sim_time()+ TIMEOUT_LOCALIZATION ;
							
							return ptr->relay;
						}
					else
						ptr = (loc_cell *)ptr->next;
			 
		}
						
	return -1; //Destination not found
}

//Returns the next hop when I have a data packet to route (whatever I am a source or a relay)
int get_next_hop_for_data_pk(Packet* pk_src , int dest_final , int src_init){
	int		next_hop;
	char	msg[200];
		
	//I search the if the node is in the neighborhood table
	next_hop = get_relay_to_neigbour_node(dest_final);
	if (next_hop != -1)
		data_debug("DATA : From Neighbour_table\n");
	if (next_hop == -1)
		{	
			//Not in the neighborhood table
			next_hop = get_relay_to_node_from_localization(dest_final,OPC_FALSE);		
			if (next_hop != -1)
				data_debug("DATA : From Neighbour_table\n");

			//The node is neither in localization nor in neighborhood table
			if (next_hop == -1)
				{
					if (is_AP) 
						{
							//We send a route_request in order to build a road to the destination
							add_in_data_pk_buffer(pk_src);													
							send_route_request(dest_final);
						}
					else 	
						{
							//I transfer the packet to the AP by sending it to the next hop toward AP (my father)
							next_hop = get_relay_to_internet();
							sprintf(msg,"DATA : RELAY data PK to Internet to %d \n", next_hop);
							data_debug(msg);
						}
				}
		}
	return(next_hop);
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   ROUTE REQUESTS
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
	char					msg[150];
	
	//If the list is empty
	if (op_prg_list_size(rreq_pk_buffer)==0)
		return;

	//Search if the entry already exists
	for (i=op_prg_list_size(rreq_pk_buffer)-1; i>=0 ; i--)
		{
			entry = (struct_rreq_pk_buffer*) op_prg_list_access (rreq_pk_buffer, i);
			
			
			if (1)//DEBUG>2)
				{
					sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
					rreq_debug(msg);
				}
			op_prg_list_remove ( rreq_pk_buffer , i);
			free(entry);
		}
}

//Timeout entries in Route Requests pk buffer
void send_timeout_in_rreq_pk_buffer(int* arg , int code){
	int						i = 0;
	struct_rreq_pk_buffer*	entry;
	char					msg[150];
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
							sprintf(msg,"RREQ-BUFFER : %d retransmits the rreq toward %d with timeout %f at %f\n", my_address , entry->dest , entry->timeout , op_sim_time());
							rreq_debug(msg);

							//Sends a new RREQ
							send_rreq_pk(entry->dest , entry->stat_id);
							
							//Info update
							entry->nb_retry ++;
							
							//We have a bigger timeout in order to have the entry if we receive a RREP with this new retry (anywhere, we won't retransmit the packet)
							if (entry->nb_retry == MAX_NB_RREQ_RETRY)
								entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER*10;
							else
								{
									entry->timeout = op_sim_time() + TIMEOUT_RREQ_PK_BUFFER;
		
									//The older entry
									if ((entry->timeout < older_entry) || (older_entry == -1))						
										older_entry = entry->timeout;
								}
							
						}
					//deletes the corresponding entry
					else					
						{
							if (DEBUG>2)
								{
									sprintf(msg,"RREQ-BUFFER : deletes the rreq toward %d with timeout %f at %f (nb_retry=%d)\n", entry->dest , entry->timeout , op_sim_time() , entry->nb_retry);
									rreq_debug(msg);
								}
							op_prg_list_remove ( rreq_pk_buffer , i);
							free(entry);
						}
				}
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;

		}
	
	if (older_entry!=-1)
		op_intrpt_schedule_call(older_entry , RREQ_RETRY_CODE, send_timeout_in_rreq_pk_buffer , i);
}

//Add the data packet in the buffered list
void add_in_rreq_pk_buffer(int dest , int stat_id){
	struct_rreq_pk_buffer*	entry;
	int						i = 1;
	if (op_prg_list_size(rreq_pk_buffer) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_RREQ_PK_BUFFER , RREQ_RETRY_CODE, send_timeout_in_rreq_pk_buffer , &i);
	
	//Memory allocation
	entry = (struct_rreq_pk_buffer*) malloc (sizeof(struct_rreq_pk_buffer));
			
	//Info
	entry->dest		= dest;
	entry->timeout	= op_sim_time() + TIMEOUT_RREQ_PK_BUFFER;
	entry->nb_retry	= 0;
	entry->stat_id	= stat_id;
	
	//I add it in the list
	op_prg_list_insert(rreq_pk_buffer, entry , OPC_LISTPOS_TAIL);	
}


void send_route_request(int addr){	
	char	msg[150];
	
	 add_in_rreq_pk_buffer(addr , stats_nb_rreq);
	 send_rreq_pk(addr , stats_nb_rreq++);
	
	 //Debug
	sprintf(msg,"\n\n !!!  RREQ : %d sends a RREQ toward %d via the backbone at %f  !!!\n", my_address , addr , op_sim_time());
	data_debug(msg);
}


//Sends the RREQ Packet
void send_rreq_pk(int addr_searched , int stat_id){
	Packet* pk_dest;
	char 	msg[200];

	// we create and send the route-request
	pk_dest = op_pk_create_fmt("somom_pk_route_request");
			
	op_pk_nfd_set(pk_dest,"SRC_INIT",		my_address);
	op_pk_nfd_set(pk_dest,"SRC",			my_address);
	op_pk_nfd_set(pk_dest,"DEST",			ADDR_MULTICAST_BACKBONE);
	op_pk_nfd_set(pk_dest,"NODE_SEARCHED",	addr_searched);
	
	op_pk_nfd_set(pk_dest,"PK_ID",			current_id++);
	op_pk_nfd_set(pk_dest,"STAT_ID",		stat_id);
	op_pk_nfd_set(pk_dest,"TTL",			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_dest,"OPTION_TYPE",	RREQ_PK_TYPE);
	
	//Stats
	stats_rreq [stat_id].source 				= my_address;
	stats_rreq [stat_id].dest 					= addr_searched;
	stats_rreq [stat_id].rreq_nb_retry ++;
	if (stats_rreq [stat_id].rrep_time_reception == 0)
		stats_rreq [stat_id].rreq_time_emission 	= op_sim_time();
	
	//Debug
	sprintf(msg,"\n\n !!!  RREQ : %d sends a RREQ toward %d via the backbone at %f  !!!\n", my_address , addr_searched , op_sim_time());
	rreq_debug(msg);
	
	//Transmission
	somom_pk_send(pk_dest);	
}

//relay a route_request to all sons and father
//void relay_route_request(Packet* pk,int addr_son){
void forward_route_request(Packet* pk_src){
	Packet	*pk_dest;
	char 	msg[200];
	int		ttl;

	//Info from source pk
	op_pk_nfd_get(pk_src, "TTL", &ttl);
	
	//Packet to send
	pk_dest = op_pk_copy(pk_src);
	op_pk_nfd_set(pk_dest, "SRC", my_address);
	op_pk_nfd_set(pk_dest, "TTL", --ttl);

	//Debug
	sprintf(msg,"RREQ : %d sent to backbone \n",my_address);
	rreq_debug(msg);

	//Transmission
	somom_pk_send_delayed(pk_dest , op_dist_uniform(0.002));	
}







//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                  ROUTE REPLY
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void send_route_reply(int addr , int stat_id){

	int addr_father;
	Packet* pk_new;
	char msg[200];
	
	// we search the address of the father
	addr_father = get_relay_to_internet();
	
	
	//send route_reply to the AP	
	pk_new = op_pk_create_fmt("somom_pk_route_reply");
	
	op_pk_nfd_set(pk_new,"SRC_INIT",		my_address);
	op_pk_nfd_set(pk_new,"SRC",				my_address);
	op_pk_nfd_set(pk_new,"DEST",			addr_father);
	op_pk_nfd_set(pk_new,"DEST_FINAL",		ADDR_MULTICAST_AP);
	op_pk_nfd_set(pk_new,"NODE_SEARCHED",	addr);
	op_pk_nfd_set(pk_new,"PK_ID",			current_id++);
	op_pk_nfd_set(pk_new,"STAT_ID",			stat_id);
	op_pk_nfd_set(pk_new,"TTL",				MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk_new,"OPTION_TYPE",		RREP_PK_TYPE);
	
	//Debug
	sprintf(msg,"RREP : %d sends a RREP to its father %d\n",my_address,addr_father);
	//printf(msg);
	rrep_debug(msg);	
	
	//Transmission
	if (ACK_FOR_RREP)
		add_unicast_ack(addr_father , current_id-1 , pk_new);
	somom_pk_send_delayed(pk_new , op_dist_uniform(0.003));
	
	//Next Send Update / Communication Expired
	communication_info.last_time_useful = op_sim_time();
	communication_info.last_time_update = op_sim_time();

	//Stats
	stats_rreq[stat_id].rreq_time_reception	= op_sim_time();
	stats_rreq[stat_id].rrep_time_emission	= op_sim_time();
	stats_rreq[stat_id].rrep_hops			= 0;
	stats_rreq[stat_id].rrep_nb_retry 		= 0;
}





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTE DELETE
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//generates a new formated route_delete
Packet* generate_route_delete(){
	packet* 	pkptr ;
	
	//create a new pk : route-delete
	pkptr = op_pk_create_fmt("somom_pk_route_delete");

	op_pk_nfd_set(pkptr ,"SRC_INIT", 		my_address);
	op_pk_nfd_set(pkptr ,"SRC", 			my_address);
	op_pk_nfd_set(pkptr ,"DEST_FINAL", 		ADDR_MULTICAST_AP);
	op_pk_nfd_set(pkptr ,"TTL", 			10);
	op_pk_nfd_set(pkptr ,"PK_ID", 		   	current_id++);
	op_pk_nfd_set(pkptr ,"OPTION_TYPE", 	RDELETE_PK_TYPE);

	return(pkptr);
}


//sends a route_delete for the corresponding destination (the route seems broken)
void send_route_delete(int addr){
	Packet		*pkptr;
	int			next_hop;
	char		msg[200];
	
	if (1)//DEBUG>1)
		{
			sprintf(msg, "INIT : %d sends a route_delete for the destination %d at %f\n", my_address , addr , op_sim_time());
			rdel_debug(msg);
		}

	//new filled route_delete
	pkptr = generate_route_delete();
	op_pk_nfd_set(pkptr , "ADDRESS1", 	addr);
	
	//next hop
	next_hop = get_relay_to_internet();
	op_pk_nfd_set(pkptr , "DEST" , next_hop);

	//transmission
	if(next_hop == -1)
		{
			sprintf(msg,"RDEL : %d can't find relay to Internet\n" , my_address);
			printf(msg);
			common_debug(msg);
		}
	else if(!is_AP)
		somom_pk_send(pkptr);

}

//Fills the route_del packet with the routes passing through addr
Boolean fill_route_delete(Packet *pk, int addr){
	loc_cell 	*ptr;
	loc_cell	*ptr_save;
	//int 		node;
	int 		index = 1;//ADDRESS_FIELD;
	char		field_name[50];
	Boolean 	is_empty = OPC_TRUE;

	//Initialization
	ptr 		= localization_table; 
	ptr_save 	= localization_table;

	//if the addr is found in the field "RELAY" we copy the name of the node in the new pk AND delete the entry
	while(ptr!=NULL)
		{
			if (ptr->relay == addr)
				{
					//we copy the addr of the node in the route-delete pk
					//node = ptr->address;
					sprintf(field_name , "ADDRESS%d" , index);
					op_pk_nfd_set(pk , field_name , ptr->address);
					
					//op_pk_fd_set(pk , index , OPC_FIELD_TYPE_INTEGER , node , 32);
					//index++;
					is_empty = OPC_FALSE;
				
					//we delete the entry in the localization table					
					if (ptr == localization_table)
						{
							localization_table = (loc_cell*)ptr->next;
							ptr_save = (loc_cell*)ptr->next;
							free(ptr);
							ptr=ptr_save;							
						}
					else
						{
							ptr_save->next = ptr->next;
							free(ptr);
							ptr = ptr_save->next;
						}
				 }			
			 else
				{
					ptr_save = ptr;
					ptr = ptr->next;
				}
			 
			}
	return (is_empty);
}






//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								ROUTE UPDATE
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void send_route_update(){
	int dest;
	char msg[200];
	Packet *pk;

	dest = get_relay_to_internet();
 
	pk=op_pk_create_fmt("somom_pk_route_update");

	op_pk_nfd_set(pk,"SRC_INIT", 		my_address);
	op_pk_nfd_set(pk,"SRC", 			my_address);
	op_pk_nfd_set(pk,"DEST", 			dest);
	op_pk_nfd_set(pk,"DEST_FINAL", 		ADDR_MULTICAST_AP);
	op_pk_nfd_set(pk,"TTL", 			MAX_NETWORK_RADIUS);
	op_pk_nfd_set(pk,"PK_ID", 		   	current_id++);
	op_pk_nfd_set(pk,"OPTION_TYPE", 	RUPDATE_PK_TYPE);
	
	if(dest==-1)
		{
			sprintf(msg,"ROUTE UPDATE : %d can't find relay to Internet\n",my_address);
			rup_debug(msg);
		}
	else
		{
			if(!is_AP)
				{			
					//Debug
					sprintf(msg,"\n\n !!!  ROUTE UPDATE : SENT by node %d at %f  !!! \n\n",my_address,op_sim_time());
					rup_debug(msg);
							
					//Transmission
					if (ACK_FOR_RUP)
						add_unicast_ack(dest , current_id-1 , pk);
					somom_pk_send(pk);
					
					//Next Send Update / Communication Expired
					communication_info.last_time_update = op_sim_time();
				}
		}
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
	ack_couple*		couple;
	char			msg[150];
	
	//If the list is empty, we must schedule the must verification of timeouts in ack_table (else it is already scheduled)
	if (op_prg_list_size (ack_table) == 0)
		{
			sprintf(msg , "!! prog next : %f\n", op_sim_time() + TIMEOUT_UNICAST_ACK);
			node_debug(msg);
			op_intrpt_schedule_self (op_sim_time() + TIMEOUT_UNICAST_ACK , UNICAST_RETRANSMISSIONS_CODE);
		}
	else
		{
			sprintf(msg , "!! deja une entree a %f\n", op_sim_time());
			node_debug(msg);
		
		}
	
	//Memory allocation (to have a valid entry outside this function)
	couple = (ack_couple*) malloc ( sizeof (ack_couple));
	
	//Info
	couple->dest		= dest;
	couple->pk_id		= pk_id;
	couple->nb_retry	= 0;
	couple->timeout 	= op_sim_time() + TIMEOUT_UNICAST_ACK ;
	couple->pkptr		= op_pk_copy(pkptr);
	
	//Insert it
	op_prg_list_insert( ack_table , couple , OPC_LISTPOS_TAIL);	
}

//This packet must be further acknowledged
void delete_unicast_ack(int dest , int pk_id){
	ack_couple*		couple;
	char			msg[200];
	int				i;
	//Info from packet for debug purpose
	int				pk_type , dest_final;
	int				nb_entry_del = 0;
	
	//If the list is empty -> I exit !
	if (op_prg_list_size(ack_table)==0)
		{
			if (DEBUG>1)
				{
					sprintf(msg, "ACKS : the entry corresponding to the pk_id %d to destination %d was not found at %f\n",pk_id, dest , op_sim_time());
					ack_debug (msg);
				}
			return ;
		}
	
	//For each entry
	for (i = op_prg_list_size(ack_table)-1 ; i >=0 ; i--)
		{
			//gets the entry
			couple = (ack_couple*) op_prg_list_access (ack_table, i);
			
			if ((couple->dest == dest) && (couple->pk_id == pk_id))
				{
					if (DEBUG>1)
						{
							op_pk_nfd_get(couple->pkptr, "OPTION_TYPE", &pk_type);
							op_pk_nfd_get(couple->pkptr, "DEST_FINAL", 	&dest_final);
							//Per node
							sprintf(msg, "ACKS : %d acked the packet with pk_id %d at %f\n", dest , pk_id , op_sim_time());
							ack_debug (msg);
						}
					op_prg_list_remove(ack_table, i);
					free(couple);
					nb_entry_del++;
				}
		}
	
	if (DEBUG>0)
		{
			sprintf(msg, "ACKS : %d entries (with pk_id %d to destination %d) were found at %f\n", nb_entry_del , pk_id , dest , op_sim_time());
			ack_debug (msg);
		}	
	 print_unicast_ack_table();
}

//Sends an unicast ack
void acknowledges_unicast_packet(int address , int pk_id){
	char		msg[150];
	Packet*		pkptr;
	
	//Creates the packet
	pkptr = op_pk_create_fmt ("somom_pk_ack");
	
	//Sets some fields
	op_pk_nfd_set (pkptr, "SRC_INIT" ,		my_address);
	op_pk_nfd_set (pkptr, "SRC" ,			my_address);
	op_pk_nfd_set (pkptr, "DEST" ,			address);
	op_pk_nfd_set (pkptr, "TTL" ,			1);
	op_pk_nfd_set (pkptr, "OPTION_TYPE" ,	ACK_APP_PK_TYPE);
	op_pk_nfd_set (pkptr, "PK_ID" ,			pk_id);

	//Sends it
	somom_pk_send_delayed(pkptr , op_dist_uniform(0.001));
	
	if (DEBUG>1)
		{
			sprintf(msg,"ACKS : we send an active ack to %d (for pk-id %d) at %f\n", address , pk_id , op_sim_time());
			ack_debug (msg);
		}
}







//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   LOCALIZATION
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Is the destination present in the localization_table?
Boolean is_in_localization_table(int addr){
	loc_cell 	*ptr;

	ptr = localization_table; 
	//Walks the localization table
	while(ptr!=NULL)
		{
			if (ptr->address == addr)
				return(OPC_TRUE);
			ptr = ptr->next;
		}
	
	//No entry was found
	return(OPC_FALSE);
}


//Delete a particular localization entry
int delete_localization_entry(int addr){
	loc_cell *ptr , *ptr_save;

	ptr = localization_table; 
	ptr_save = localization_table;
	
	while(ptr!=NULL)
	{
			if (ptr->address == addr)
				{
					if (ptr == localization_table) //The particular case of a delete entry in head of the list 
							{
								localization_table = (loc_cell*)ptr->next;
								free(ptr);
								return 0; 
							}
						else
							{
								ptr_save->next = ptr->next;
								free(ptr);
								return 0;
							}
				}
			
			ptr_save = ptr;
			ptr = (loc_cell*)ptr->next;
		}
	}
	

//Delete all the entries contained in the fields ADDRESSx in pk
void delete_old_entry(Packet *pk){
	int		addr_node;
	int	 	index = 1;
	char	field_name[50];

	//For each address contained in the packet
	for(index = 1 ; index <= MAX_NB_NODES_IN_RDEL ; index++) 
		{
			sprintf(field_name , "ADDRESS%d" , index);
			op_pk_nfd_get(pk , "field_name" , &addr_node);
		
			//Delete the entry in the localization entry
			delete_localization_entry(addr_node);
		}
}

//Updates an entry in the localization table
void update_localization_table(int addr_src, int addr_relay){
	loc_cell 	*ptr;
	loc_cell	*ptr_save;
	
	ptr 		= localization_table; 
	ptr_save 	= localization_table;

	while(ptr != NULL)
		{
			//If an entry is found, it is updated and we exit the function
			if (ptr->address == addr_src)
				{
					ptr->timeout 	= op_sim_time() + TIMEOUT_LOCALIZATION;
					ptr->relay 		= addr_relay;
					return;
				}
			
			//Next Cell
			ptr_save = ptr;
			ptr = ptr->next;
		}

	//We create a cell

	ptr = (loc_cell*) malloc(sizeof(loc_cell));
	if (ptr == NULL)
		printf("error in the memory allocation for the creation of a new cell in the localization table");

	ptr->address		= addr_src;
	ptr->relay			= addr_relay;
	ptr->timeout		= op_sim_time() + TIMEOUT_LOCALIZATION;	
	ptr->next			= localization_table;
	localization_table 	= ptr;
}




//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//		   		                   DATA
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

Packet* generate_data_pk(int dest_final){
	Packet*		pkptr;
	int 		stat_id;

	//INCOMING PACKET 
	pkptr = op_pk_create_fmt ("somom_pk_data");
	op_pk_total_size_set ( pkptr, data_pk_size * 8 );
	op_pk_nfd_set (pkptr, "SRC_INIT", 	my_address);
	op_pk_nfd_set (pkptr, "SRC", 		my_address);
	op_pk_nfd_set (pkptr, "DEST_FINAL",	dest_final);
	op_pk_nfd_set (pkptr, "PK_ID", 		current_id);
	op_pk_nfd_set (pkptr, "STAT_ID", 	stats_nb_data_pk);
	op_pk_nfd_set (pkptr, "TTL", 		MAX_NETWORK_RADIUS);
	op_pk_nfd_set (pkptr, "OPTION_TYPE",DATA_PK_TYPE);

	//STATS
	if (stats_nb_data_pk > MAX_DATA_PK)
		op_sim_end("We have too many data packet to handle the stats", "please increase the value of MAX_DATA_PK","in the header block of somom","");
	stats_data_pk	[stats_nb_data_pk].source			= my_address;
	stats_data_pk	[stats_nb_data_pk].dest				= dest_final;
	stats_data_pk	[stats_nb_data_pk].pk_size			= (int) op_pk_total_size_get(pkptr);
	stats_data_pk	[stats_nb_data_pk].time_generation	= op_sim_time();

	//Old Stats
	update_time_table(CREATED,pkptr,OPC_TRUE);
	update_time_table(SENT , pkptr , OPC_TRUE);
	
	//DEBUG
	stat_id = stats_nb_data_pk;
	
	//Control
	current_id++;
	stats_nb_data_pk++;
	if (is_AP)
		stats_nb_data_pk_down++;
	else
		stats_nb_data_pk_up++;
	
	return(pkptr);
}


void schedule_data_pk(int dest_final , int code){

	//COMMON FOR COMMUNICATING NODES
	communication_info.last_time_update = op_sim_time();
	communication_info.last_time_useful = op_sim_time();

	//PK Generation + Transmission
	send_data_pk(  generate_data_pk(dest_final)  );		
}

void send_data_pk(Packet* pkptr){
	char 	msg[300];
	int 	dest_final;
	int		next_hop;
	int		stat_id , pk_id;
	
	//Common fields
	pk_id = current_id;
	op_pk_nfd_set(pkptr , "SRC",		my_address);
	op_pk_nfd_get(pkptr , "PK_ID",		&pk_id);
	op_pk_nfd_get(pkptr , "STAT_ID",	&stat_id);
	op_pk_nfd_get(pkptr , "DEST_FINAL",	&dest_final);
	
	//Stats
	stats_data_pk	[stat_id].source		= my_address;
	stats_data_pk 	[stat_id].time_emission	= op_sim_time();
	
	//Route
	next_hop = get_next_hop_for_data_pk(pkptr , dest_final , my_address); 
	op_pk_nfd_set(pkptr , "DEST", next_hop);

	//DEBUG
	if (DEBUG)
		{
			sprintf(msg, "\n\n !!!  DATA-INIT : %d sends a data pk to %d at %f (stat_id %d pk_id %d)!!!\n",my_address , dest_final , op_sim_time(),stat_id, pk_id);
			data_debug(msg);
		}
				
	//Only If we have a valid route
	if (next_hop != -1)
		{
			//Debug		
			sprintf(msg,"DATA : %d sent to %d toward %d\n",my_address , next_hop , dest_final);
			data_debug(msg);

			//Stats
			update_time_table(SENT , pkptr , OPC_FALSE);
		
			//Acks
			if (ACK_FOR_DATA)
				add_unicast_ack(next_hop , pk_id , pkptr);

			//Transmission
			somom_pk_send(pkptr);	
			
		}
	else
		{
			sprintf(msg,"DATA : %d not sent to %d toward %d (no route)\n",my_address , next_hop , dest_final);
			data_debug(msg);
		}
}


//Sends all buffered data packet for the destination (return FALSE if not pk was found in the buffer)
Boolean send_data_pk_buffer(int destination , int hops){
	int					i = 0;
	struct_pk_buffer*	entry;
	char				msg[150];
	Boolean				is_found = OPC_FALSE; //at least one entry was found
	int					stat_id , pk_id , src;
	
	
	//I send a paging reply, I found the destination !
	if ((is_AP) && (is_paging_activated))
		{
			send_paging_rep(destination , hops);
		}
	// I simply empty my data-buffer
	else
		{
			//If the list is empty
			if (op_prg_list_size(data_pk_buffer)==0)
				return(OPC_FALSE);
	
			//Search if the entry already exists
			for (i=op_prg_list_size(data_pk_buffer)-1 ; i>=0 ;i--)
				{
					entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
					//We delete the entry
					if ((entry->dest == destination) && (entry->timeout >= op_sim_time()))
						{	
							//DEBUG
							if (DEBUG>-1)
								{
									op_pk_nfd_get(entry->packet, "SRC_INIT",&src);
									op_pk_nfd_get(entry->packet, "STAT_ID", &stat_id);
									op_pk_nfd_get(entry->packet, "PK_ID", 	&pk_id);
									sprintf(msg,"\n\n-------  DATA-PK : data-pk from %d to %d at %f (timeout %f)  (with at least 1 RREQ) (stat_id %d pk_id %d)   -------\n", src , entry->dest , op_sim_time(), entry->timeout, stat_id , pk_id);
									data_debug(msg);
								}
					
							//Sends the packet
							send_data_pk(entry->packet);
			
							//deletes the corresponding entry
							op_prg_list_remove ( data_pk_buffer , i);
							free(entry);
							is_found = OPC_TRUE;
						}
				}
	
			return(is_found);
		}

}

//Deletes timeouted entries in data pk buffer
void delete_timeout_in_data_pk_buffer(int code, int unused){
	int					i = 0;
	struct_pk_buffer*	entry;
	double				older_entry = -1;
	char				msg[150];
	
	//If the list is empty
	if (op_prg_list_size(data_pk_buffer)==0)
		return;
	
	//For each entry
	for (i=op_prg_list_size(data_pk_buffer)-1; i >=0; i--)
		{
			entry = (struct_pk_buffer*) op_prg_list_access (data_pk_buffer, i);
			
			//We delete the entry
			if (entry->timeout <= op_sim_time())
				{				
					//DEBUG
					if (DEBUG>2)
						{
							sprintf(msg,"DATA-BUFFER : deletes the packet to %d with timeout %f at %f\n", entry->dest , entry->timeout , op_sim_time());
							common_debug(msg);
							data_debug(msg);
						}
					
					//deletes the corresponding entry
					op_prg_list_remove ( data_pk_buffer , i);
					free(entry);
				}
			//Older Remaining Entry
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;
		}
	if (older_entry != -1)
		op_intrpt_schedule_call(older_entry , 0 , delete_timeout_in_data_pk_buffer , 0);
}

//Add the data packet in the buffered list
void add_in_data_pk_buffer(Packet *pk_dest){
	struct_pk_buffer*	entry;
	int					dest;
	
	//Delete Timeouted entries Verification
	if (op_prg_list_size (data_pk_buffer) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_DATA_PK_BUFFER , 0 , delete_timeout_in_data_pk_buffer , 0);
	
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





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								COMMON NETWORK
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//returns the address of a node which can receive a data packet
int get_a_not_sleeping_address(){
	Boolean	is_remote_id_valid = OPC_FALSE;
	int		*is_remote_sleeping , *is_remote_AP;
	int		*its_address;
	int		network_id;
	int		node_remote_id;
	int		process_remote_id;
	char	msg[500];

	while (!is_remote_id_valid)
		{				
				//Identificaiton of the remote localization process
				network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
				node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
				process_remote_id	= op_id_from_name (node_remote_id, OPC_OBJMTYPE_QPS, LOCALIZATION_PROCESS_NAME);
				//This error catch does not function, an error is generated whatever I do
				if (process_remote_id == OPC_OBJID_INVALID){
					sprintf(msg , "the process name %s is invalid" , LOCALIZATION_PROCESS_NAME);
					op_sim_end("Error" , msg , "Please change it in the cdcl_biblio.h" , "");
				}
				
				//Is this node allowed to communicate ?
				is_remote_sleeping 	= op_ima_obj_svar_get(process_remote_id , "is_sleeping_authorized");
				is_remote_AP	 	= op_ima_obj_svar_get(process_remote_id , "is_AP");
				its_address	= op_ima_obj_svar_get(process_remote_id , "my_address");
				
				//It must be:
				//- a non sleeping node
				//- not AP
				//- not me, of course
				is_remote_id_valid = (*is_remote_sleeping == OPC_FALSE) && (*is_remote_AP == OPC_FALSE) && (*its_address != my_address);				
		}
	
	return(*its_address);
}

//returns the address of a node which can receive a data packet
int get_a_not_sleeping_process_id(){
	Boolean	is_remote_id_valid = OPC_FALSE;
	int		*is_remote_sleeping , *is_remote_AP;
	int		network_id;
	int		node_remote_id;
	int		process_remote_id;
	char	msg[500];

	while (!is_remote_id_valid)
		{				
				//Identificaiton of the remote localization process
				network_id 			= op_id_parent ( op_id_parent( op_id_self() ) );
				node_remote_id		= op_id_from_sysid(OPC_OBJTYPE_NDMOB, op_dist_uniform(op_topo_child_count(network_id , OPC_OBJTYPE_NDMOB))    );
				process_remote_id	= op_id_from_name (node_remote_id, OPC_OBJMTYPE_QPS, LOCALIZATION_PROCESS_NAME);
				//This error catch does not function, an error is generated whatever I do
				if (process_remote_id == OPC_OBJID_INVALID){
					sprintf(msg , "the process name %s is invalid" , LOCALIZATION_PROCESS_NAME);
					op_sim_end("Error" , msg , "Please change it in the cdcl_biblio.h" , "");
				}
				
				//Is this node allowed to communicate ?
				is_remote_sleeping 	= op_ima_obj_svar_get(process_remote_id , "is_sleeping_authorized");
				is_remote_AP	 	= op_ima_obj_svar_get(process_remote_id , "is_AP");
				
				//It must be:
				//- a non sleeping node
				//- not AP
				//- not me, of course
				is_remote_id_valid = (*is_remote_sleeping == OPC_FALSE) && (*is_remote_AP == OPC_FALSE);		
		}
	return(process_remote_id);
}


//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void somom_stats_about_control_pk_flows(Packet* pkptr){
	char	msg[50];
	int		option_type;
	int		type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);
	
	//Update Stats
	switch(option_type)
		{
			case DATA_PK_TYPE :
				nb_pk_somom_data_instantaneous++;
				nb_pk_somom_data_total++;
			break;
			case RREQ_PK_TYPE :
				nb_pk_somom_rreq_instantaneous++;
				nb_pk_somom_rreq_total++;
			break;
			case RREP_PK_TYPE :
				nb_pk_somom_rrep_instantaneous++;
				nb_pk_somom_rrep_total++;
			break;
			case RUPDATE_PK_TYPE :
				nb_pk_somom_rup_instantaneous++;
				nb_pk_somom_rup_total++;
			break;
			case RDELETE_PK_TYPE :
				nb_pk_somom_rdel_instantaneous++;
				nb_pk_somom_rdel_total++;
			break;
			case ACK_APP_PK_TYPE :
				nb_pk_somom_ack_instantaneous++;
				nb_pk_somom_ack_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}

//Set some stats about nerwork control flows
//Type = type of contro packet (HELLO, CLUSTER, CDS or OTHER)
void somom_stats_about_control_pk_flows_retransmission(Packet* pkptr){
	char	msg[50];
	int		option_type;
	
	//Get Option type
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &option_type);

	//Update Stats
	switch(option_type)
		{
			case DATA_PK_TYPE :
				nb_pk_somom_data_retransmission_instantaneous++;
				nb_pk_somom_data_retransmission_total++;
			break;
			case RREP_PK_TYPE :
				nb_pk_somom_rrep_retransmission_instantaneous++;
				nb_pk_somom_rrep_retransmission_total++;
			break;
			default :
				sprintf(msg,"But we don't find the packet type '%d'", option_type);
				op_sim_end("We want to update statistics about packet transmissions", msg , "" , "");
			break;
		}
}


//Sends the packet with the specified delay
void somom_pk_send_delayed(Packet* pkptr , double delay){
	int		address_dest;
	int		pk_type;
	
	//Stats
	somom_stats_about_control_pk_flows(pkptr);

	//Gathers some infos
	op_pk_nfd_get (pkptr, "DEST", &address_dest);
	op_pk_nfd_get (pkptr, "OPTION_TYPE", &pk_type);
	
	//Transmission
	op_pk_send_delayed(pkptr , STRM_TO_LOWER , delay);
}

//Sends the packet without delay
void somom_pk_send (Packet* pkptr){
	somom_pk_send_delayed(pkptr , 0);
}


//Retransmits the packet with the specified delay
void somom_pk_retransmit_delayed(Packet* pkptr , double delay){
	
	//Stats
	somom_stats_about_control_pk_flows_retransmission(pkptr);

	//Sends it
	op_pk_send_delayed(pkptr, STRM_TO_LOWER , delay);
}

//Retransmits the packet without delay
void somom_pk_retransmit (Packet* pkptr){
	somom_pk_retransmit_delayed(pkptr , 0);
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

//Writes in ack_debug file the list of packets remaining to be acknowledged
void print_unicast_ack_table(){
	ack_couple*		couple;
	char			msg[200];
	int				i;
	
	ack_debug   ("--------------------------------------------------------\n");
	sprintf(msg,"|                  ACK TABLE (%d)                        |\n", my_address);
	ack_debug(msg);
	ack_debug   ("--------------------------------------------------------\n");
	ack_debug("DEST	|	PK_ID	|	NB_RETRY	|	TIMEOUT\n");
	//For each entry
	for (i = 0 ; i < op_prg_list_size(ack_table) ; i++)
		{
			//gets the entry
			couple = (ack_couple*) op_prg_list_access (ack_table, i);
			
			sprintf(msg, "%d	|	%d	|	%d		|	%f	\n",couple->dest , couple->pk_id , couple->nb_retry , couple->timeout);
			ack_debug(msg);			
		}
	ack_debug("\n");
}



void write_node_stat(){

	FILE* 	stat_file;
	char	str[200];
	
	time_pk_table *ptr = time_table;

	if (my_address<10)
		sprintf(str,"results_somom/stats_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(str,"results_somom/stats_per_node/results_%d.txt",my_address);
	
	stat_file = fopen(str,"w");
	fprintf(stat_file,"------------------------------------------------\n");
	fprintf(stat_file,"------------------- NODE %d --------------------\n",my_address);
	fprintf(stat_file,"------------------------------------------------\n\n\n");
	
	// print the stats about the SENT PK
	
	fprintf(stat_file,"------------- DATA PACKETS SENT ----------------\n");
	fprintf(stat_file,"	PK_ID	|	SRC	|	DEST	|	TIME	|\n");
		
	while (ptr != NULL)
		{
			if(ptr->src==my_address)
				{
					fprintf(stat_file,"	%d	|	%d	|	%d	|	%f		|\n", ptr->pk_id , ptr->src , ptr->dest , ptr->time_sent);
			
				}
			ptr = (time_pk_table *) ptr->next;
		}
	
	// print the stats about the RECEIVED PK
	
	fprintf(stat_file,"------------- DATA PACKETS RECEIVED ----------------\n");
	fprintf(stat_file,"	PK_ID	|	SRC	|	DEST	|	TIME	|\n");
	
	ptr=time_table;
	
	while (ptr != NULL)
		{
			if(ptr->dest==my_address)
				{
					fprintf(stat_file,"	%d	|	%d	|	%d	|	%f		|\n", ptr->pk_id , ptr->src , ptr->dest , ptr->time_received);
				}
			ptr = (time_pk_table *) ptr->next;
		}
	
			
	fclose(stat_file);


}


void write_sons(){
		char		msg[1550];
		int			i;
		son			*ptr_son;

		ptr_son = my_cds->sons;
		i=0;
		node_debug("List of Sons :\n");
		while(ptr_son!=NULL)
			{
				sprintf(msg,"%d   |   ",ptr_son->address);i++;
				node_debug(msg);
				ptr_son = (son *)ptr_son->next;
			}
		node_debug("\n");
		sprintf(msg,"(%d sons)\n\n",i);
		node_debug(msg);

}

void write_dominatees(){
		char		msg[1550];
		dominatee	*ptr_dominatee;
		int			i;
		
		ptr_dominatee = my_cds->dominatees;
		i=0;
		node_debug("List of Dominatees : \n");
		while(ptr_dominatee!=NULL)
			{
				sprintf(msg,"%d   |   ",ptr_dominatee->address);
				node_debug(msg);
				ptr_dominatee = ptr_dominatee->next;
				i++;
			}
		node_debug("\n");
		sprintf(msg,"(%d Dominatees)\n\n",i);
		node_debug(msg);

}


void node_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	if (my_address<10)
		sprintf(str,"results_somom/details_per_node/results_0%d.txt",my_address);
	if (my_address>=10)
		sprintf(str,"results_somom/details_per_node/results_%d.txt",my_address);
		
	fichier = fopen(str,"a");
	fprintf(fichier,message);
	fclose(fichier);
}


void data_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_data.txt",begin_name_stats);
		
		if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}

void rrep_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_rrep.txt",begin_name_stats);
		
	if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}

void rreq_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_rreq.txt",begin_name_stats);
	if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}
void rup_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_route_update.txt",begin_name_stats);
		
	if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}

void ack_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_ack.txt",begin_name_stats);
		
		if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}
void common_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_common.txt",begin_name_stats);
		
		if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}
void rdel_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_rdel.txt",begin_name_stats);
		
	if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}
void paging_debug(char* message){
	FILE* 	fichier;
	char	str[200];

	sprintf(str,"results_somom/%d_somom_debug_paging.txt",begin_name_stats);
		
	if (DEBUG>1)
		{
			fichier = fopen(str,"a");
			fprintf(fichier,message);
			fclose(fichier);
		}
}





//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								STATS
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//Writes in an array all stats for data pk
void update_time_table(int type , Packet *pk , Boolean pk_local){

int pk_id;
int	src;
int dest;
	
time_pk_table *ptr = time_table;
time_pk_table *ptr_save = time_table;


op_pk_nfd_get(pk,"SRC",				&src);
op_pk_nfd_get(pk,"DEST_FINAL",		&dest);
op_pk_nfd_get(pk,"PK_ID",			&pk_id);

if (type == CREATED) // we complete the created_time variable and the src - dest variables
	{
		
		if (ptr == NULL)  //time_table is empty
			{
				if((ptr = (time_pk_table*) malloc(sizeof(time_pk_table)))==NULL)
					printf("error in the memory allocation for the creation of a new cell in the localization table\n");
				else
					{
						ptr->next			= NULL;
						ptr->time_created	= op_sim_time();
						ptr->time_sent		= -1;
						ptr->time_received	= -1;
						ptr->pk_id			= pk_id;
						ptr->src			= src;
						ptr->dest			= dest;
						time_table			= ptr;
							
				   	}

			}
		else
			{	// we go to the end of the list
				while (ptr != NULL)
					{
						ptr_save=ptr;
						ptr= (time_pk_table*)ptr->next;
					}
   
				//we create a  new cell at the end of the list
				if((ptr = (time_pk_table*) malloc(sizeof(time_pk_table)))==NULL)
					printf("error in the memory allocation for the creation of a new cell in the localization table");
				else
					{
						ptr->next			= NULL;
						ptr->time_created	= (float)op_sim_time();
						ptr->time_sent		= -1;
						ptr->time_received	= -1;
						ptr->pk_id			= pk_id;
						ptr->src			= src;
						ptr->dest			= dest;
						ptr_save->next		= (struct time_pk_table*) ptr;
						
							
				   	}
				
			}
		
   	}
if (type == SENT)	// we complete the sent_time variable 
	{
	while (ptr != NULL)
		{
			if (ptr->pk_id == pk_id)
				{
					ptr->time_sent 	= (float)op_sim_time();
					ptr->pk_local 	= pk_local;
					ptr 			= (time_pk_table *) ptr->next;
				}
			else
				ptr = (time_pk_table *) ptr->next;
		
		}
		
	}

if (type == RECEIVED)	// we complete the received_time variable and calculate the new sum_delivery_delay
	{
	while (ptr != NULL)
		{
			if (ptr->pk_id == pk_id)
				{
					ptr->time_received		= (float)op_sim_time();				
					ptr = (time_pk_table *) ptr->next;
				}
			else
				ptr = (time_pk_table *) ptr->next;
		
		}
		
	}
}






//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//
//								PAGING (DOWNLOAD)
//
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


// A paging is scheduled
void schedule_paging(int dest_final, int code){
	Packet		*pkptr;
	int			ap_dest;
	char		msg[200];
	
	
	//Generation of the data pk
	pkptr =  generate_data_pk(dest_final);	
	
	//The destination is already known
	ap_dest = get_ap_for_dest_in_paging_routing_table(dest_final);
	if (ap_dest != -1)
		{
			if (DEBUG > 2)
				{
					sprintf(msg, "\nPAGING : forwards the data-pk to the ap %d for %d (already in paging_table) at %f\n\n", ap_dest , dest_final , op_sim_time());
					paging_debug(msg);
				}
			send_paging_ack(pkptr , ap_dest);
		}
	// I send a paging request
	else
		{
			send_paging_req(dest_final);
			add_paging_pk(pkptr);
		}
}

//I send a paging request via my ethernet link
void send_paging_req(int dest_final){
	Packet	*pkptr;
	char	msg[200];
		
	if (DEBUG>2)
		{
			sprintf(msg, "\n!!!! PAGING : %d sends a paging-req for %d at %f !!!!!!\n\n", my_address , dest_final , op_sim_time());
			paging_debug(msg);
		}
	
	pkptr = op_pk_create_fmt("somom_pk_paging_req");
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "DEST" , 			BROADCAST);
	op_pk_nfd_set(pkptr , "NODE_SEARCHED" , dest_final);
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	PAGING_REQ_PK_TYPE);			
	op_pk_send_delayed(pkptr , STRM_TO_LOWER , op_dist_uniform(0.001));
}


//I send a paging request via my ethernet link
void send_paging_rep(int dest_final , short hops){
	Packet	*pkptr;
	char	msg[200];
	
	if (DEBUG>2)
		{
			sprintf(msg, "PAGING : %d sends a paging-rep for %d at %f\n", my_address , dest_final , op_sim_time());
			paging_debug(msg);
		}
	
	pkptr = op_pk_create_fmt("somom_pk_paging_rep");
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "DEST" , 			ADDR_MULTICAST_PAGING_MASTER);
	op_pk_nfd_set(pkptr , "NODE_SEARCHED" , dest_final);
	op_pk_nfd_set(pkptr , "HOPS" , 			hops);
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	PAGING_REP_PK_TYPE);			
	op_pk_send_delayed(pkptr , STRM_TO_LOWER ,  op_dist_uniform(0.001));
}

//I send a paging delete via my ethernet link
void send_paging_del(int dest_final){
	Packet	*pkptr;
	char	msg[200];
		
	if (DEBUG>2)
		{
			sprintf(msg, "PAGING : %d sends a paging-del for %d at %f\n", my_address , dest_final , op_sim_time());
			paging_debug(msg);
		}

	pkptr = op_pk_create_fmt("somom_pk_paging_del");
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "DEST" , 			BROADCAST);
	op_pk_nfd_set(pkptr , "NODE_SEARCHED" , dest_final);
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	PAGING_DEL_PK_TYPE);			
	op_pk_send_delayed(pkptr , STRM_TO_LOWER ,  op_dist_uniform(0.001));
}

//I send a paging request via my ethernet link
void send_paging_ack(Packet* pk_data , int  ap_dest){
	Packet	*pkptr;
	char	msg[200];
		
	if (DEBUG>2)
		{
			sprintf(msg, "PAGING : %d sends a paging-ack to %d at %f\n", my_address , ap_dest , op_sim_time());
			paging_debug(msg);
		}

	pkptr = op_pk_create_fmt("somom_pk_paging_ack");
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "DEST" , 			ap_dest);
	op_pk_nfd_set(pkptr , "DATA" , 			pk_data);
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	PAGING_ACK_PK_TYPE);			
	op_pk_send_delayed(pkptr , STRM_TO_LOWER ,  op_dist_uniform(0.001));
}


//I send a paging request via my ethernet link
void send_paging_rep_gratuitous(int code1, int code2){
	Packet		*pkptr;
	char		msg[200];
	char		field_name[50];
	neigh_cell	*ptr;
	int		   	i;
		
	if (DEBUG>10)
		{
			sprintf(msg, "PAGING : %d sends a paging-rep-gratuitous at %f\n", my_address , op_sim_time());
			paging_debug(msg);
		}

	pkptr = op_pk_create_fmt("somom_pk_paging_rep_gratuitous");
	op_pk_nfd_set(pkptr , "SRC" , 			my_address);
	op_pk_nfd_set(pkptr , "DEST" , 			ADDR_MULTICAST_PAGING_MASTER);
	op_pk_nfd_set(pkptr , "OPTION_TYPE" , 	PAGING_REP_GRATUITOUS_PK_TYPE);			
	
	//each known node
	ptr= neighbour_table;
	i=1;
	while (ptr != NULL)
		{
			if ((ptr->bidirect) && (ptr->address != my_address))
				{
					if (i > MAX_NB_NODES_IN_PAGING_REP)
						op_sim_end("Fatal Error", "we have too many nodes to place in a paging_rep_gratuitous", "please increase the available place in the pk","and the value of MAX_NB_NODES_IN_PAGING_REP in the header bock"); 
				
					sprintf(field_name , "NODE_%d",i);
					op_pk_nfd_set(pkptr , field_name , ptr->address);				
					sprintf(field_name , "HOPS_%d",i);
					op_pk_nfd_set(pkptr , field_name , ptr->hops);				
					i++;
				}
			ptr = ptr->next;
		}
	
	//empty unused fields
	while (i <= MAX_NB_NODES_IN_PAGING_REP)
		{
			sprintf(field_name , "NODE_%d",i);
			op_pk_nfd_strip(pkptr , field_name);				
			sprintf(field_name , "HOPS_%d",i);
			op_pk_nfd_strip(pkptr , field_name);				
			i++;		
		}

	//transmission
	op_pk_send_delayed(pkptr , STRM_TO_LOWER ,  op_dist_uniform(0.001));
	
	//Next one
	op_intrpt_schedule_call(op_sim_time() + INTERVALL_PAGING_REP , 0 , send_paging_rep_gratuitous , 0);
}



//--------------------------------  PAGING BUFFER --------------------------------




//This packet is in paging mode
void add_paging_pk(Packet* pk_src){

	//Insert it
	op_prg_list_insert( paging_buffer , op_pk_copy(pk_src) , OPC_LISTPOS_TAIL);	
}

//This destination for paging was found
void empty_paging_buffer(int dest , int ap){
	int		i;
	Packet*	pkptr;
	double	time_generated;
	
	
	//For each entry
	for (i = op_prg_list_size(paging_buffer)-1 ; i >=0 ; i--)
		{
			//gets the entry
			pkptr = (Packet*) op_prg_list_access (paging_buffer, i);
			
			time_generated = op_pk_creation_time_get(pkptr);
			if (time_generated > op_sim_time() - TIMEOUT_PAGING_BUFFER)
				{					
					send_paging_ack(op_pk_copy(pkptr) , ap);
					op_prg_list_remove(paging_buffer, i);
					op_pk_destroy(pkptr);
				}
		}	
}

//for debug
void print_paging_buffer(){
	Packet*			pkptr;
	char			msg[400];
	int				i;
	
	paging_debug("--------------------------------------------------------\n");
	paging_debug("|                  PAGING BUFFER                        |\n");
	paging_debug("--------------------------------------------------------\n");
	paging_debug("	PK_ID		|	TIME_CREATION	\n");
	
	//For each entry
	for (i = 0 ; i < op_prg_list_size(paging_buffer) ; i++)
		{
			//gets the entry
			pkptr = (Packet*) op_prg_list_access (paging_buffer, i);
			
			sprintf(msg, "%f	|	%f	\n", op_pk_id(pkptr) , op_pk_creation_time_get(pkptr));
			paging_debug(msg);			
		}
	paging_debug("\n");

}




//--------------------------------  PAGING ROUTING TABLE --------------------------------





//Returns the associated AP for a particular node in the paging routing table
//If no AP is founs, returns -1
int get_ap_for_dest_in_paging_routing_table(int dest){
	struct_paging	*entry;
	int				i;
	int				best_ap , best_hops;
	
	//default values (not found)
	best_ap 	= -1;
	best_hops	= 99999;

	//updates the entry
	for (i=op_prg_list_size(paging_routing_table)-1; i >=0; i--)
		{
			entry = (struct_paging*) op_prg_list_access (paging_routing_table, i);
			
			if ((entry->dest == dest) && (entry->timeout >= op_sim_time()) && (entry->hops < best_hops))
				{
					best_ap		= entry->ap;
					best_hops	= entry->hops;
				}
		}
	
	//No entry was found for this destination
	return(best_ap);
}


//extracts from the packet pkptr the nodes which are covered, and adds them in the paging_routing_table
void add_nodes_in_paging_routing_table(Packet *pkptr){
	int		i;
	char	field_name[50];
	int		addr , hops , src;

	
	//The AP originator
	op_pk_nfd_get(pkptr , "SRC" , &src);
	
	i=1;
	sprintf(field_name , "NODE_%d", i);
	while(op_pk_nfd_is_set(pkptr , field_name))
		{
			//extracts the info
			op_pk_nfd_get(pkptr , field_name , &addr);
			sprintf(field_name , "HOPS_%d", i);
			op_pk_nfd_get(pkptr , field_name , &hops);
			
			//Adds this node and ap couple
			add_in_paging_routing_table(addr , src , hops);
		
			//Next field
			i++;
			sprintf(field_name , "NODE_%d", i);
		}
	
}


//Adds an AP as serving a particular destination
void add_in_paging_routing_table(int dest , int ap , short hops){
	struct_paging	*entry;
	int				i;
	Boolean			is_found = OPC_FALSE;
	char			msg[200];
	
	//schedules the next paging_routing_table verification
	if (op_prg_list_size(paging_routing_table) == 0)
		op_intrpt_schedule_call(op_sim_time() + TIMEOUT_PAGING_ROUTING_TABLE * INTERVALL_PAGING_REP , 0 , delete_timeout_in_paging_routing_table , 0);
	
	//updates the entry
	for (i=op_prg_list_size(paging_routing_table)-1; i >=0; i--)
		{
			entry = (struct_paging*) op_prg_list_access (paging_routing_table, i);
			
			if (entry->dest == dest)
				{
					//The new entry is better than the previous old entry
					if  ((entry->hops < hops) || (entry->ap == ap))
						{
							entry->ap 		= ap;
							entry->hops 	= hops;
							entry->timeout	= op_sim_time() + TIMEOUT_PAGING_ROUTING_TABLE * INTERVALL_PAGING_REP;
							is_found = OPC_TRUE;
					
							if (DEBUG>2)
								{
									sprintf(msg,"PAGING : updates the entry in paging_routing table to %d (AP=%d) with timeout %f at %f\n", entry->dest , entry->ap , entry->timeout , op_sim_time());
									paging_debug(msg);
								}
						}
					//The entry is not the best, but it was found !
					else						
						is_found = OPC_TRUE;
				}
		}	
	
	if (!is_found)
		{
			//Or creates a new one
			entry = (struct_paging*) malloc (sizeof(struct_paging));
	
			entry->dest 	= dest;
			entry->ap		= ap;
			entry->hops		= hops;
			entry->timeout	= op_sim_time() + TIMEOUT_PAGING_ROUTING_TABLE * INTERVALL_PAGING_REP;
	
			//Insert it
			op_prg_list_insert( paging_routing_table , entry , OPC_LISTPOS_TAIL);	
			
			if (DEBUG>2)
				{
					sprintf(msg,"PAGING : adds the entry in paging_routing table to %d (AP=%d) with timeout %f at %f\n", entry->dest , entry->ap , entry->timeout , op_sim_time());
					paging_debug(msg);
				}
		}	
}


//Delete timeouted entries
void delete_timeout_in_paging_routing_table(int code, int unused){
	int				i = 0;
	struct_paging	*entry;
	double			older_entry = -1;
	char			msg[150];
	
	//If the list is empty
	if (op_prg_list_size(paging_routing_table)==0)
		return;
	
	//For each entry
	for (i=op_prg_list_size(paging_routing_table)-1; i >=0; i--)
		{
			entry = (struct_paging*) op_prg_list_access (paging_routing_table, i);
			
			//We delete the entry
			if (entry->timeout <= op_sim_time())
				{				
					//DEBUG
					if (DEBUG>2)
						{
							sprintf(msg,"PAGING : deletes the entry in paging_routing table to %d (AP=%d) with timeout %f at %f\n", entry->dest , entry->ap , entry->timeout , op_sim_time());
							paging_debug(msg);
						}
					
				
					//deletes the corresponding entry
					op_prg_list_remove ( paging_routing_table , i);
					free(entry);
				}
			//Older Remaining Entry
			else if ((entry->timeout < older_entry) || (older_entry == -1))
				older_entry = entry->timeout;
		}
	if (older_entry != -1)
		op_intrpt_schedule_call(older_entry , 0 , delete_timeout_in_paging_routing_table , 0);
}

//For debug
void print_paging_routing_table(){
	struct_paging*	entry;
	char			msg[200];
	int				i;
	
	paging_debug("--------------------------------------------------------\n");
	paging_debug("|                 PAGING ROUTING TABLE                  |\n");
	paging_debug("--------------------------------------------------------\n");
	paging_debug("	DEST	|	AP	|	TIMEOUT	\n");
	
	//For each entry
	for (i = 0 ; i < op_prg_list_size(paging_routing_table) ; i++)
		{
			//gets the entry
			entry = (struct_paging*) op_prg_list_access (paging_routing_table, i);
			
			sprintf(msg, "	%d	|	%d	|	%f	\n", entry->dest , entry->ap , entry->timeout);
			paging_debug(msg);			
		}
	paging_debug("\n");

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
	void somom_process (void);
	Compcode somom_process_init (void **);
	void somom_process_diag (void);
	void somom_process_terminate (void);
	void somom_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
somom_process (void)
	{
	int _block_origin = 0;
	FIN (somom_process ());
	if (1)
		{


		FSM_ENTER (somom_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "Init", "somom_process () [Init enter execs]")
				{
				//Synchronisation with lower levels
				//op_intrpt_schedule_self(op_sim_time() + 45.0,0);
				
				if (begin_name_stats == 0)
					begin_name_stats = time(NULL);
				
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC,0);
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,somom_process)


			/** state (Init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "Init", "somom_process () [Init exit execs]")
				{
				}


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init", "Init2")
				/*---------------------------------------------------------*/



			/** state (Init2) enter executives **/
			FSM_STATE_ENTER_FORCED (1, state1_enter_exec, "Init2", "somom_process () [Init2 enter execs]")
				{
				char		str[100];
				FILE*		fichier;
				int			i;
				int			node_id;
				int			nb_normal_nodes;
				neigh_cell	**neigh_tmp;
				int			*ap_tmp;
				int			*address_tmp;
				
				
				
				
				/* -- initialization -- */
				communication_info.is_important 	= OPC_FALSE;
				communication_info.last_time_update	= -999;
				communication_info.last_time_useful	= -999;
				
				srand(op_dist_uniform(64000));
				
				
				/*----------------- Simulation Attributes -----------------*/
				
				node_id 		= op_topo_parent(op_id_self());
				cdcl_process_id = op_id_from_name(node_id, OPC_OBJTYPE_PROC , "cds-cluster");
				
				
				neigh_tmp			= op_ima_obj_svar_get(cdcl_process_id , "neighbour_table");
				neighbour_table		= *neigh_tmp;
				my_cds 			 	= op_ima_obj_svar_get(cdcl_process_id , "my_cds");
				ap_tmp				= op_ima_obj_svar_get(cdcl_process_id ,	"is_AP");
				is_AP				= *ap_tmp;
				if (is_AP)
					_somom_nb_aps++;
				address_tmp			= op_ima_obj_svar_get(cdcl_process_id ,	"my_address");
				my_address			= *address_tmp;
				if (my_address == 1)
					is_paging_master = OPC_TRUE;
				else
					is_paging_master = OPC_FALSE;
				
				
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"NB_CONNECTIONS", 				&nb_connections);
				op_ima_sim_attr_get(OPC_IMA_DOUBLE, "INTERN_COMMUNICATIONS_RATIO", 	&intern_com_ratio);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"DEBUG_LOC", 					&DEBUG);
				op_ima_sim_attr_get(OPC_IMA_INTEGER,"DATA_PK_SIZE", 				&data_pk_size);
				if (nb_nodes == 0)
					{
						op_ima_sim_attr_get(OPC_IMA_INTEGER,"IS_PAGING_ACTIVATED", 	&is_paging_activated);
						op_ima_sim_attr_get(OPC_IMA_DOUBLE, "RATIO_SLEEPING_NODES",	&ratio_of_sleeping_nodes);
					}
				
				//--------------------- Opening files --------------------
				
				if (my_address<10)
						sprintf(str,"results_somom/details_per_node/results_0%d.txt",my_address);
				if (my_address>=10)
						sprintf(str,"results_somom/details_per_node/results_%d.txt",my_address);
				fichier = fopen(str,"w");
				fclose(fichier);
				
				
				
				
				//----------------------- Stats ---------------------
				
				//protection against arrays overflows
				if (my_address >= MAX_ADDRESS)
					op_sim_end("We have too many nodes","please increase the value of MAX_ADDRESS","in the header block of the cdcl_routing process","");
				if (nb_nodes >= MAX_NB_NODES)
					op_sim_end("We have too many nodes","please increase the value of MAX_NB_NODES","in the header block of the cdcl_routing process","");
				
				
				my_stat_id = nb_nodes++;							//The first node has id 0
				address_to_stat_id	[my_address] = my_stat_id;		//Convert an address into an id
				stat_id_to_address	[my_stat_id] = my_address;		//The inverse
				
				for (i=0; i < MAX_DATA_PK ; i++)
					{
						stats_rreq[i].source					= 0;
						stats_rreq[i].dest						= 0;
						stats_rreq[i].rreq_time_emission		= 0;
						stats_rreq[i].rreq_time_reception		= 0;
						stats_rreq[i].rreq_nb_retry				= 0;
						stats_rreq[i].rrep_time_emission		= 0;
						stats_rreq[i].rrep_time_reception		= 0;
						stats_rreq[i].rrep_hops					= 0;
						stats_rreq[i].rrep_nb_retry				= 0;
					}
				for (i=0; i < MAX_DATA_PK ; i++)
					{
						stats_data_pk[i].source					= 0;
						stats_data_pk[i].dest					= 0;
						stats_data_pk[i].pk_size				= 0;
						stats_data_pk[i].hops					= 0;
						stats_data_pk[i].nb_retry				= 0;
						stats_data_pk[i].time_emission			= 0;
						stats_data_pk[i].time_reception			= 0;
					}
				
				
				
				
				
				
				//----------------------- Lists ---------------------
				
				rreq_pk_buffer 			=  op_prg_list_create();
				rreq_pk_buffer 			=  op_prg_mem_alloc (sizeof(List));
				
				ack_table 				=  op_prg_list_create();
				ack_table 				=  op_prg_mem_alloc (sizeof(List));
				
				data_pk_buffer			=  op_prg_list_create();
				data_pk_buffer			=  op_prg_mem_alloc (sizeof(List));
				
				paging_routing_table	=  op_prg_list_create();
				paging_routing_table	=  op_prg_mem_alloc (sizeof(List));
				
				paging_buffer			=  op_prg_list_create();
				paging_buffer			=  op_prg_mem_alloc (sizeof(List));
				
				
				
				
				
				//--------------------- Packets ---------------------
				
				current_id = op_dist_uniform (1000);
				
				
				
				
				
				//----------------- Sleeping Mode -------------------
				
				//Number of nodes not AP
				nb_normal_nodes = nb_nodes - _somom_nb_aps;
				
				//Formula to decide if the node is allowed to sleep or not
				if (   (!is_AP) &&   ( (nb_normal_nodes * ratio_of_sleeping_nodes) - current_nb_sleeping_nodes_allowed >= 1 )   )
					{
						is_sleeping_authorized = OPC_TRUE;
						current_nb_sleeping_nodes_allowed++;
					}
				else
					is_sleeping_authorized = OPC_FALSE;
					
					
					
					
				//------------------ INTERRUPTIONS------------------
				//Data Transmission
				if (is_AP)
					{
						if ((is_paging_master) || (!is_paging_activated))
							for (i=0; i < nb_connections; i++)
								op_intrpt_schedule_self (TIME_BEGIN_DATA + op_dist_uniform( (double) INTERVALL_DATA_PK_AP) , PK_DATA_GENERATE_CODE);
					}
				else if ((nb_connections > actual_nb_connections) && (!is_sleeping_authorized))
					{
						op_intrpt_schedule_self (TIME_BEGIN_DATA + op_dist_uniform( (double) INTERVALL_DATA_PK_AP / DATA_PK_UPLOAD_RATIO ) , PK_DATA_GENERATE_CODE);
						actual_nb_connections++;
					}
				
				//Route Update if Usefull
				op_intrpt_schedule_self (op_sim_time() + op_dist_uniform( (double)TIMEOUT_ROUTE_UPDATE), SEND_UPDATE_CODE);
				
				
				//I send gratuitous Paging_Rep if I am an AP and the paging is activated
				if ((is_AP) && (is_paging_activated))
					op_intrpt_schedule_call(op_sim_time() + INTERVALL_PAGING_REP , 0 , send_paging_rep_gratuitous , 0);
				}


			/** state (Init2) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "Init2", "somom_process () [Init2 exit execs]")
				{
				}


			/** state (Init2) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "Init2", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, state2_enter_exec, "idle", "somom_process () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,somom_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "idle", "somom_process () [idle exit execs]")
				{
				//printf ("%d - %d - %d - %d - %d\n", op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_SELF, OPC_INTRPT_STRM, OPC_INTRPT_ENDSIM);
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (PK_FROM_LOWER)
			FSM_TEST_COND (DIE)
			FSM_TEST_COND (PK_DATA_GENERATE)
			FSM_TEST_COND (ENDSIM)
			FSM_TEST_COND (UNICAST_RETRANSMISSIONS)
			FSM_TEST_COND (SEND_UPDATE)
			FSM_TEST_COND (STATE_CHANGED)
			FSM_TEST_COND (SON_LOST)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 3, state3_enter_exec, ;, "PK_FROM_LOWER", "", "idle", "PK_from_LOWER")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "DIE", "", "idle", "DEAD")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "PK_DATA_GENERATE", "", "idle", "DATA")
				FSM_CASE_TRANSIT (3, 6, state6_enter_exec, ;, "ENDSIM", "", "idle", "ENDSIM")
				FSM_CASE_TRANSIT (4, 7, state7_enter_exec, ;, "UNICAST_RETRANSMISSIONS", "", "idle", "RET_UNICAST")
				FSM_CASE_TRANSIT (5, 8, state8_enter_exec, ;, "SEND_UPDATE", "", "idle", "SEND_UPDATE")
				FSM_CASE_TRANSIT (6, 9, state9_enter_exec, ;, "STATE_CHANGED", "", "idle", "STATE_CHANGED")
				FSM_CASE_TRANSIT (7, 10, state10_enter_exec, ;, "SON_LOST", "", "idle", "SON_LOST")
				}
				/*---------------------------------------------------------*/



			/** state (PK_from_LOWER) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "PK_from_LOWER", "somom_process () [PK_from_LOWER enter execs]")
				{
				//PK Fields
				Packet	*pk_src;
				Packet	*pk_data;
				int		packet_type;
				int		dest_final;
				int		dest = 0;
				int		src;
				int		src_init;
				int		node_searched = 0;
				short	ttl;
				short	hops;
				int		pk_id	= 0;
				int		stat_id = 0;
				//Control
				char  		msg[200];
				Boolean		is_valid;
				
				
				// Obtain the incoming packet.	
				if (!op_strm_empty(STRM_FROM_LOWER))
					pk_src = op_pk_get (op_intrpt_strm ());
				
				
				
				
				//Gather information needed
				op_pk_nfd_get(pk_src,"DEST_FINAL", 	&dest_final);
				op_pk_nfd_get(pk_src,"DEST", 		&dest);
				op_pk_nfd_get(pk_src,"SRC_INIT", 	&src_init);
				op_pk_nfd_get(pk_src,"SRC",			&src);
				
				op_pk_nfd_get(pk_src,"OPTION_TYPE", &packet_type);
				op_pk_nfd_get(pk_src,"TTL", 		&ttl);
				op_pk_nfd_get(pk_src,"PK_ID", 		&pk_id);
				op_pk_nfd_get(pk_src,"STAT_ID", 	&stat_id);
				
				
				//Error (pk unknown ot not for a not-dominator)
				if ((my_cds->state != DOMINATOR) && (packet_type != DATA_PK_TYPE) && (packet_type !=  ACK_APP_PK_TYPE) && (packet_type !=  RDELETE_PK_TYPE) && (packet_type != RUPDATE_PK_TYPE) && (!is_AP)){
						printf("!!!! %d is not a dominator and it received a control packet (neither data nor ack) (type=%d) !!!!!!!!!\nI probably changed my state (useless dominator), and the network didn't have the time to update my state",my_address, packet_type);
						is_valid = OPC_FALSE;
					}
				else
					{
					
				switch (packet_type){
					//PAGING
						//The node "destination" is searched. Is this node in my services area ?
						case PAGING_REQ_PK_TYPE :
							if ((dest == BROADCAST) || (dest == my_address))
								{
									//Sends A RREQ toward the searched node
									op_pk_nfd_get(pk_src , "NODE_SEARCHED", &node_searched);
									send_route_request(node_searched);
								}
						break;
						
						
						//I register the source as an AP source for the destination
						case PAGING_REP_PK_TYPE :
							if ((is_paging_master) && (dest == ADDR_MULTICAST_PAGING_MASTER))
								{
									//Adds the dest-AP couple in the paging_table
									op_pk_nfd_get(pk_src , "NODE_SEARCHED", &node_searched);
									op_pk_nfd_get(pk_src , "HOPS", 			&hops);
									add_in_paging_routing_table(node_searched , src , hops);
						
									//sends the corresponding buffered packets
									empty_paging_buffer(node_searched , src);
									
									//Advertise that the node was found
									send_paging_del(node_searched);
								}
						break;
						
						
						//I register the source as an AP source for the destinations
						case PAGING_REP_GRATUITOUS_PK_TYPE :
							if ((is_paging_master) && (dest == ADDR_MULTICAST_PAGING_MASTER))
								add_nodes_in_paging_routing_table(pk_src);
						break;
						
						
						//I register the source as an AP source for the destination
						case PAGING_DEL_PK_TYPE :
							if ((dest == BROADCAST) || (dest == my_address))
								{
									//This entry was found elsewhere, no further RREQ is required
									op_pk_nfd_get(pk_src , "NODE_SEARCHED", &node_searched);
									delete_entry_in_rreq_buffer(node_searched);
								}
						break;
				
						
						//I must send the packet (contained in the data field)
						case PAGING_ACK_PK_TYPE :
							if ((dest == BROADCAST) || (dest == my_address))
								{
									op_pk_nfd_get(pk_src , "DATA", &pk_data);
									send_data_pk(pk_data);
								}
						break;
						
						
					//ACKS	
						//The node acknowledges my one packet
						case ACK_APP_PK_TYPE :
							delete_unicast_ack(src , pk_id);
							sprintf(msg,"ACK : %d received an ack from %d\n", my_address , src);
							ack_debug(msg);
						break;
						
						
					//DATA
						case DATA_PK_TYPE:
						//Active Acks
							if (ACK_FOR_DATA)
								{
									acknowledges_unicast_packet(src, pk_id);
									sprintf(msg,"ACK : %d sends an ack to %d\n", my_address , src);
									ack_debug(msg);
								}
								
						//Localization table Update
							//I create an entry in my localization_table for the "source node"
								if (my_cds->state == DOMINATOR)
										update_localization_table(src_init , src);
									
						//We are the final destination	
							if(((dest_final==my_address) && (dest==my_address))    ||    ((dest_final==ADDR_MULTICAST_AP) && (is_AP) && (dest==my_address)))
							 	{				
									// STATS
									update_time_table(RECEIVED , pk_src , OPC_FALSE); 
									
									//DEBUG
									sprintf(msg,"!!!  DATA - FINAL DEST : %d (%d) received pk from %d via %d at %f (stat_id %d pk_id %d) !!!\n\n",my_address , my_cds->state , src_init , src , op_sim_time(), stat_id , pk_id);
									data_debug(msg);
				
									//Stats
									stats_data_pk 	[stat_id].time_reception	= op_sim_time();
									stats_data_pk	[stat_id].hops				= MAX_NETWORK_RADIUS - ttl + 1;
									
									//we have a too big offset between our current stat_id and the stat_id of the received pk, we have certainly one error
									if (stat_id - stats_nb_data_pk > 20)
										{
											printf("%d -> %d\n",stat_id , stats_nb_data_pk);
											op_sim_end("","","","");
										}
							
									//The next Communication expired
									communication_info.last_time_useful = op_sim_time();
								
								}
						//We must relay this packet
							else if(dest == my_address)
								{	
									//Stats (only for Debug, If the packet is finally received, this value is updated according to end-to-end information)
									stats_data_pk 	[stat_id].hops++;
								
									//Next hop to the AP (Internet Pk)
									if((dest_final == ADDR_MULTICAST_AP) && (!is_AP)) 
										dest = get_relay_to_internet();
									else	
									//Next hop in localization/neighborhood table
										dest = get_next_hop_for_data_pk(pk_src , dest_final , src_init);
											
									//Relays it
									if (dest != -1)
										{
											//Fields
											op_pk_nfd_set(pk_src , "DEST",	dest);
											op_pk_nfd_set(pk_src , "SRC",		my_address);
											op_pk_nfd_set(pk_src , "TTL",		--ttl);
											
											//Transmission
											if (ACK_FOR_DATA)
												add_unicast_ack(dest , pk_id , pk_src);
											somom_pk_send(op_pk_copy(pk_src));
										
											//Debug
											sprintf(msg,"DATA : %d relays to %d toward %d at %f (stat_id %d pk_id %d)\n",my_address , dest , dest_final , op_sim_time(), stat_id , pk_id);
											//printf(msg);
											data_debug(msg);
										}
								}
							
						break;
					
						
						case RREQ_PK_TYPE:
							op_pk_nfd_get(pk_src,"DEST", &dest);
						
							if((dest==ADDR_MULTICAST_BACKBONE) || (dest==my_address))
								{
									// we get the address of the searched node
									op_pk_nfd_get(pk_src,"NODE_SEARCHED", 	&node_searched);
									
									if ( (node_searched==my_address) || (must_rreq_proxy(node_searched)) )
										{
											//DEBUG
											sprintf(msg,"\n\n !!!  RREQ : %d sends a RREP (as proxy or for itself) at %f  !!! \n\n\n",my_address , op_sim_time());
											rreq_debug(msg);
											rrep_debug(msg);
											
											send_route_reply(node_searched , stat_id);
										}	
									else
										{
											sprintf(msg, "RREQ : %d forwards the RREQ from %d via %d at %f (%d searched)\n", my_address, src_init , src , op_sim_time() , node_searched);
											rreq_debug(msg);
											forward_route_request(pk_src);
										}
								}		
						
						break;
					
						case RREP_PK_TYPE:
							//Active Acks
							if (ACK_FOR_RREP)
								{
									acknowledges_unicast_packet(src, pk_id);
									sprintf(msg,"ACK : %d sends an ack to %d\n", my_address , src);
									ack_debug(msg);
								}
						
							op_pk_nfd_get(pk_src,"NODE_SEARCHED", 	&node_searched);
						
							if((is_AP) && (dest == my_address))
								{
									//Stats - New
									stats_rreq[stat_id].rrep_hops			= MAX_NETWORK_RADIUS - ttl + 1;
									stats_rreq[stat_id].rrep_time_reception	= op_sim_time();
									
									//Debug
									sprintf(msg, "\n\n!!! RREP : %d received a RREP from %d via %d at %f !!!\n\n",my_address , node_searched , src , op_sim_time());
									//printf(msg);
									rrep_debug(msg);
									data_debug(msg);
									
									//We don't have to send route_request for that node anymore
									delete_entry_in_rreq_buffer(node_searched);
									
									//We create an entry in my localization_table for the "node_searched"
									update_localization_table(node_searched , src);
				
									//we send the bufferized packet to the relay
									send_data_pk_buffer(node_searched , MAX_NETWORK_RADIUS - ttl + 1);					
								}
							else if ((dest == my_address) && (my_cds->state == DOMINATOR))
								{
									//We create an entry in my localization_table for the "node_searched"
									update_localization_table(node_searched , src);
							
									//we search the address of the father
									dest = get_relay_to_internet();
									op_pk_nfd_set(pk_src,"SRC", 	my_address);
									op_pk_nfd_set(pk_src,"DEST", 	dest);
									op_pk_nfd_set(pk_src , "TTL",	--ttl);
								
									//Debug
									if (DEBUG>1)
										{
											sprintf(msg,"RREP : %d relayed to %d toward %d at %f\n", my_address , dest , dest_final , op_sim_time());
											rrep_debug(msg);
										}
									
									//Transmission
									if (ACK_FOR_RREP)
										add_unicast_ack(dest , pk_id , pk_src);
									somom_pk_send(op_pk_copy(pk_src));				
								}
						break;
					
						case RUPDATE_PK_TYPE:
							//Active Acks
							if (ACK_FOR_RUP)
								{
									acknowledges_unicast_packet(src , pk_id);
									sprintf(msg,"ACK : %d sends an ack to %d\n", my_address , src);
									ack_debug(msg);
								}
									
							//We create an entry in my localization_table for the "node_searched"
							//update_localization_table(src_init , src);
						
							if((is_AP)&&(dest==my_address))
								{
									sprintf(msg,"ROUTE UPDATE : %d received a Route Update from %d at %f\n", my_address , src_init , op_sim_time());
									rup_debug(msg);
								}
							else if(dest==my_address)
								{										
									//we search the address of the father
									dest=get_relay_to_internet();					
									if(dest == -1)
										{
											sprintf(msg,"ROUTE UPDATE : %d can't find relay to Internet\n", my_address);
											//printf(msg);
											rup_debug(msg);
										}
									else
										{			
											//Common Fields
											op_pk_nfd_set(pk_src,"DEST",	dest);
											op_pk_nfd_set(pk_src,"SRC", 	my_address);
											op_pk_nfd_set(pk_src , "TTL",	--ttl);
									
											//Debug
											sprintf(msg,"ROUTE UPDATE : %d relayed to %d\n",my_address , dest);
											//printf(msg);
											rup_debug(msg);
									
											//Transmission
											if (ACK_FOR_RUP)
												add_unicast_ack(dest , pk_id , pk_src);
											somom_pk_send(op_pk_copy(pk_src));
										}												
							   	}
						
						break;
					
						case RDELETE_PK_TYPE:
							//Active Acks
							if (ACK_FOR_RDEL)
								{
									acknowledges_unicast_packet(src , pk_id);
									sprintf(msg,"ACK : %d sends an ack to %d\n", my_address , src);
									ack_debug(msg);
								}
						
							//We read the route-delete and delete the corresponding entries in the localization table
							if((is_AP) && (dest==my_address))
								{
									//Debug
									if (DEBUG>1)
										{
											sprintf(msg,"	RDEL : %d received for %d at %f\n", my_address , src_init , op_sim_time());
											rdel_debug(msg);
										}
									
									delete_old_entry(pk_src);
								}
							else if(dest==my_address)
								{										
									//We read the route-delete and delete the corresponding entries in the localization table
									delete_old_entry(pk_src);					
									
									//we search the address of the father
									dest = get_relay_to_internet();
									
									
									if(dest == -1)
										{
											//Debug
											sprintf(msg, "RDEL : %d can't find relay to Internet\n",my_address);
											rdel_debug(msg);
										}
									else
										{			
											//Sets some common fields
											op_pk_nfd_set(pk_src,"SRC",		 	my_address);
											op_pk_nfd_set(pk_src,"DEST", 		dest);
											op_pk_nfd_set(pk_src , "TTL",		--ttl);
														
											//Debug
											if (DEBUG>1)
												{
													sprintf(msg,"	RDEL : %d relayed to %d toward %d at %f\n", my_address , dest , dest_final , op_sim_time());
													rdel_debug(msg);
												}
				
											//Transmission
											if (ACK_FOR_RDEL)
												add_unicast_ack(dest , pk_id , pk_src);
											somom_pk_send(op_pk_copy(pk_src));
										}												
							   	}
					
						break;
						
				
						default:
							printf("LOC - Pk_FROM_LOWER => Type de paquet inconnu : %d !!!!!!!!!!!!!!!\n", packet_type);
							op_pk_print(pk_src);
						break;	
					}
				}	
				
				
				//The packet was treated, we destroy it to free memory
				op_pk_destroy(pk_src);
				
				
				}


			/** state (PK_from_LOWER) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "PK_from_LOWER", "somom_process () [PK_from_LOWER exit execs]")
				{
				}


			/** state (PK_from_LOWER) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "PK_from_LOWER", "idle")
				/*---------------------------------------------------------*/



			/** state (DEAD) enter executives **/
			FSM_STATE_ENTER_UNFORCED (4, state4_enter_exec, "DEAD", "somom_process () [DEAD enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (9,somom_process)


			/** state (DEAD) exit executives **/
			FSM_STATE_EXIT_UNFORCED (4, "DEAD", "somom_process () [DEAD exit execs]")
				{
				}


			/** state (DEAD) transition processing **/
			FSM_TRANSIT_MISSING ("DEAD")
				/*---------------------------------------------------------*/



			/** state (DATA) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "DATA", "somom_process () [DATA enter execs]")
				{
				int		dest_final;
				int		next_source;
				int		i;
				int		process_remote_id;
				Packet	*pkptr;
				double	delay;
				
				//------------------------------------------------------------------------------------------
				//								   THE FINAL DESTINATION
				//------------------------------------------------------------------------------------------
				
				//The final destination is random if we are the AP, but is the AP if we are a classical node
				if (!is_AP)
					{
						if (op_dist_uniform (1.0) > intern_com_ratio)
							dest_final	= ADDR_MULTICAST_AP;
						else
							dest_final	= get_a_not_sleeping_address();
						
						process_remote_id = get_a_not_sleeping_process_id();
						
					}
				else
					{
					
						//If it is an extern communication, I choose a random intern node
						if (op_dist_uniform (1.0) >= intern_com_ratio)
							dest_final	= get_a_not_sleeping_address();
						//If it is an intern communication, I reduce the probability to send a data packet (I am a privileged node)
						else if (op_dist_uniform (1.0) <= 1 / (nb_nodes * nb_connections) )
							dest_final = get_a_not_sleeping_address();
						else
							dest_final = -1;
					}
				
				
				
				//------------------------------------------------------------------------------------------	
				//								  NEXT TRANSMISSIONS
				//------------------------------------------------------------------------------------------
				
				if (dest_final != -1)
					for(i=0; i < NB_PK_PER_FLOW ; i++)
						{
							delay = i*INTERARRIVAL_DATA_PK + op_dist_uniform(0.01);
							
							//The source is an AP
							if (is_AP)
								{
									//In paging, I schedule, a data pk to "page"
									if (is_paging_activated)
										op_intrpt_schedule_call(delay + op_sim_time() , 0 , schedule_paging , dest_final);
									else
									//Else, I send directly a data pk, as a source
										op_intrpt_schedule_call(delay + op_sim_time() , 0 , schedule_data_pk , dest_final);
								}
							//Normal node -> I send a data pk
							else
								op_intrpt_schedule_call(delay + op_sim_time() , 0 , schedule_data_pk , dest_final);
						}
					
				//-------------------------------------------------------------------------------------------
				//								  NEXT DATA FLOW
				//-------------------------------------------------------------------------------------------					
				//I must wake up the next source node
				
				
				if (is_AP)
					op_intrpt_schedule_self  (op_sim_time() + op_dist_exponential(INTERVALL_DATA_PK_AP*NB_PK_PER_FLOW) , PK_DATA_GENERATE_CODE);
				else
					{
						//If the number of nodes is inferior to the number of simultaneous connections (several connections per node)
						if (nb_connections > actual_nb_connections)
							{
								op_intrpt_schedule_self (op_sim_time() + op_dist_uniform( (double) INTERVALL_DATA_PK_AP / DATA_PK_UPLOAD_RATIO ) , PK_DATA_GENERATE_CODE);
								actual_nb_connections++;
							}
				
						//As usual, we weak up randomly the next source
						op_intrpt_schedule_remote(op_sim_time() + op_dist_exponential( (double)INTERVALL_DATA_PK_AP * NB_PK_PER_FLOW / DATA_PK_UPLOAD_RATIO) , PK_DATA_GENERATE_CODE , process_remote_id);
					}
				
				}


			/** state (DATA) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "DATA", "somom_process () [DATA exit execs]")
				{
				}


			/** state (DATA) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "DATA", "idle")
				/*---------------------------------------------------------*/



			/** state (ENDSIM) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "ENDSIM", "somom_process () [ENDSIM enter execs]")
				{
				//write_node_stat();
				
				
				
				
					char	filename[200];
					FILE 	*file , *rreq_file , *data_file;
					int		i;
					//DATA TOTAL
					int		pk_size								= 0;
					double	delay_data_pk 						= 0;
					int		nb_data_pk_received					= 0;
					int		throughput_data_pk					= 0;
					int		hops_data_pk						= 0;
					int		nb_retransmissions_data_pk			= 0;
					//DATA UP
					double	up_delay_data_pk 					= 0;
					int		up_nb_data_pk_received				= 0;
					int		up_nb_data_pk_sent					= 0;
					int		up_throughput_data_pk				= 0;
					int		up_hops_data_pk						= 0;
					int		up_nb_retransmissions_data_pk		= 0;
					//DATA DOWN
					double	down_delay_data_pk 					= 0;
					int		down_nb_data_pk_received			= 0;
					int		down_nb_data_pk_sent				= 0;
					int		down_throughput_data_pk				= 0;
					int		down_hops_data_pk					= 0;
					int		down_nb_retransmissions_data_pk		= 0;
					//RREQ
					int		nb_rreq_sent						= 0;
					int		nb_retry_for_rreq					= 0;
					int		nb_retry_for_success_rreq			= 0;
					int		nb_success_rreq_with_non_null_nb_retry	= 0;
					//RREP
					int		nb_rrep_received					= 0;
					int		nb_rrep_transmitted					= 0;
					double	average_delay_for_rrep				= 0;
					double	average_delay_for_rreq_to_final_rrep= 0;
					int		average_nb_retransmissions_rrep 	= 0;
					int		hops_rrep							= 0;
					//SPEED
				   	double	SOMOM_SPEED_HIGH_MIN 	= 0;
				   	double	SOMOM_SPEED_HIGH_MAX 	= 0;
				   	double	SOMOM_SPEED_LOW_MIN 	= 0;
				   	double	SOMOM_SPEED_LOW_MAX 	= 0;
					int		somom_speed_class		= 0;
				   	//ENERGY
					sleeping_struct		*cdcl_sleeping;
					double				ratio_of_sleeping_nodes;
				
				
					
					//-----------------------------------
					// PAGING
					//-----------------------------------
					if (my_address == 1)
						{
							print_paging_buffer();
							print_paging_routing_table();
						}
				
					
					//Get the forecasted simulation duration
					op_ima_sim_attr_get(OPC_IMA_INTEGER,	"seed",			&seed);
					op_ima_sim_attr_get(OPC_IMA_INTEGER,	"DATA_PK_SIZE",	&pk_size);
						
					//-----------------------------------
					// SPEEDS
					//-----------------------------------
					if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
						{
							op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &somom_speed_class);
							switch(somom_speed_class)		
								{
									case SOMOM_LOW_SPEED :
										nb_somom_low_speed_nodes++;
									break;
									case SOMOM_HIGH_SPEED :
										nb_somom_high_speed_nodes++;
									break;
								}
						}
					
					//-----------------------------------
					// ENERGY
					//-----------------------------------
					cdcl_sleeping = op_ima_obj_svar_get(cdcl_process_id , "is_sleeping");
					somom_sleeping_total += cdcl_sleeping->cumul_sleeping_time;
						
						
						
				//Global Stats
					if (my_stat_id+1 == nb_nodes)
						{
							//-------------------
							//       SPEED
							//-------------------
							//General Parameters
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MIN", 	&SOMOM_SPEED_HIGH_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_HIGH_MAX",	&SOMOM_SPEED_HIGH_MAX); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MIN", 	&SOMOM_SPEED_LOW_MIN); 
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "SP_LOW_MAX",	&SOMOM_SPEED_LOW_MAX); 
							
							
							//-------------------
							//       ENERGY
							//-------------------
							op_ima_sim_attr_get(OPC_IMA_DOUBLE, "RATIO_SLEEPING_NODES",	&ratio_of_sleeping_nodes);
				
							//-------------------
							//       DATA
							//-------------------
							sprintf(filename,"results_somom/%d_somom_debug_pk_data.txt",begin_name_stats);		
							data_file = fopen(filename , "w");
							fprintf(data_file,"SRC	|	DEST	|	SIZE	|	HOPS	|	RETRY	|	GENERATION	|	SENT		|	REC		|	DELAY\n");	
				
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									if (stats_data_pk[i].source > _somom_nb_aps)
										up_nb_data_pk_sent++;
									else
										down_nb_data_pk_sent++;
									//The packet was received
									if (stats_data_pk [i].time_reception != 0)
										{
										//TOTAL
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;
										//UP
											if (stats_data_pk[i].source > _somom_nb_aps)
												{
													up_nb_data_pk_received++;
													up_throughput_data_pk 			+= stats_data_pk [i].pk_size;
													up_hops_data_pk 				+= stats_data_pk [i].hops;
													up_nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
													up_delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;
												}
										//DOWN
											else
												{
													down_nb_data_pk_received++;
													down_throughput_data_pk 		+= stats_data_pk [i].pk_size;
													down_hops_data_pk 				+= stats_data_pk [i].hops;
													down_nb_retransmissions_data_pk += stats_data_pk [i].nb_retry;
													down_delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;
												}
										}
									fprintf(data_file,"%d	|	%d	|	%d	|	%d	|	%d	|	%f	|	%f	|	%f	|	%f \n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].pk_size, stats_data_pk[i].hops , stats_data_pk[i].nb_retry , stats_data_pk[i].time_generation , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception,stats_data_pk[i].time_reception-stats_data_pk[i].time_emission);
								}
							fclose(data_file);
							
							//-------------------
							//	ROUTE REQUEST
							//-------------------
							sprintf(filename,"results_somom/%d_somom_debug_pk_rreq.txt",begin_name_stats);		
							rreq_file = fopen(filename , "w");
							fprintf(rreq_file,"SRC	|	DEST	|	SENT		|	REC		|	RETRY	|	SENT		|	REC		|	HOPS	|	RETRY\n");
				
							nb_rreq_sent = stats_nb_rreq;
							for (i=0 ;  i < stats_nb_rreq ; i++ )
								{
									//Nb of RREQ per route discovering
									nb_retry_for_rreq += stats_rreq [i].rreq_nb_retry;
									
									//Nb of RREQ that create a RREP
									if (stats_rreq [i].rreq_time_reception != 0)
										nb_rrep_transmitted++;							
									
							//-------------------
							//	ROUTE REPLY
							//-------------------
									if (stats_rreq[i].rrep_time_reception != 0)
										{
											nb_rrep_received++;
											hops_rrep	 					+= stats_rreq [i].rrep_hops;
											average_nb_retransmissions_rrep += stats_rreq [i].rrep_nb_retry;							
											
											//Delays for S(RREQ)->S(RREP) & D(RREP)->S(RREP)
											average_delay_for_rrep 					+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rrep_time_emission;
											average_delay_for_rreq_to_final_rrep 	+= stats_rreq [i].rrep_time_reception - stats_rreq [i].rreq_time_emission;
											//Nb RREQ per successfull route discovering
											nb_retry_for_success_rreq				+= stats_rreq [i].rreq_nb_retry;
											nb_success_rreq_with_non_null_nb_retry ++;
										}
									
									fprintf(rreq_file,"%d	|	%d	|	%f	|	%f	|	%d	|	%f	|	%f	|	%d	|	%d\n", stats_rreq[i].source , stats_rreq[i].dest , stats_rreq[i].rreq_time_emission , stats_rreq[i].rreq_time_reception , stats_rreq[i].rreq_nb_retry , stats_rreq[i].rrep_time_emission , stats_rreq[i].rrep_time_reception , stats_rreq[i].rrep_hops , stats_rreq[i].rrep_nb_retry );
								}
							fclose(rreq_file);
							
							
							//-----------------------------------
							// FILE Opening
							//-----------------------------------
				
							sprintf(filename,"results_somom/%d_somom_results_global.txt",begin_name_stats);		
							file=fopen(filename,"w");		
							if (file==NULL) 
								printf("I cannot create/open the file for statistics results\n");
						
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                 SIMULATION PARAMETERS                                       |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Number of route request retry					:	%d\n",				MAX_NB_RREQ_RETRY);
							fprintf(file, "Time between route update packets				:	%f\n",				TIMEOUT_ROUTE_UPDATE);
							fprintf(file, "Time of validity of a given route				:	%f\n",				TIMEOUT_LOCALIZATION);
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SOMOM_SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SOMOM_SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_somom_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SOMOM_SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SOMOM_SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_somom_low_speed_nodes);
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes					:	%d\n", 				nb_connections);
							fprintf(file, "Data packet size							:	%d\n", 						pk_size);
							fprintf(file, "Ratio of Intern Communications				:	%f\n", 					intern_com_ratio);
							fprintf(file, "\n\n");
				
									
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                         DATA                                               |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "TOTAL\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			stats_nb_data_pk );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) nb_data_pk_received / (double)stats_nb_data_pk );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk / (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk / (1024 * 8 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk / nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							fprintf(file,"\n\n");
						
							fprintf(file, "UP (Node->AP)\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			up_nb_data_pk_sent);
							fprintf(file, "Nb Packets Received						:	%d\n",  			up_nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) up_nb_data_pk_received / (double)up_nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) up_delay_data_pk / (double)up_nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) up_throughput_data_pk / (1024 * 8 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) up_hops_data_pk / up_nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) up_nb_retransmissions_data_pk / up_hops_data_pk );
							fprintf(file,"\n\n");
						
							fprintf(file, "DOWN (AP->Node)\n");
							fprintf(file, "Nb Packets Sent							:	%d\n",  			down_nb_data_pk_sent );
							fprintf(file, "Nb Packets Received						:	%d\n",  			down_nb_data_pk_received );
							fprintf(file, "Delivery Ratio							:	%f\n", 				(double) down_nb_data_pk_received / (double)down_nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) down_delay_data_pk / (double)down_nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) down_throughput_data_pk / (1024 * 8 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) down_hops_data_pk / down_nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) down_nb_retransmissions_data_pk / down_hops_data_pk );
							fprintf(file,"\n\n");
						
									
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                      ROUTE CONTROL                                         |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n------------------------------------------------------- ROUTE REQUEST ---------------------------------------\n");
							fprintf(file, "Nb RREQ Sent							:	%d\n",  			stats_nb_rreq );
				//			fprintf(file, "Nb packets per RREQ Sent					:	%f\n",  		(double) stats_nb_pk_for_all_rreq / stats_nb_rreq );
							fprintf(file, "Percentage of Successfull RREQ				:	%f\n", 			(double) nb_rrep_transmitted / stats_nb_rreq );
							fprintf(file, "End To End Delay 1 RREQ -> 1 RREP				:	%f\n", 		(double) average_delay_for_rreq_to_final_rrep / nb_rrep_received );
							fprintf(file, "Average nb of RREQ per route discovering			:	%f\n", 		(double) nb_retry_for_rreq / stats_nb_rreq);
							fprintf(file, "Average nb of RREQ per successfull route discovering	:	%f\n", 	(double) nb_retry_for_success_rreq / nb_success_rreq_with_non_null_nb_retry);
							fprintf(file, "\n");
							fprintf(file, "\n------------------------------------------------------- ROUTE REPLY ---------------------------------------\n");
							fprintf(file, "Nb RREP Transmitted						:	%d\n",  			nb_rrep_transmitted );
							fprintf(file, "Nb RREP Received							:	%d\n",  			nb_rrep_received );
							fprintf(file, "Percentage of Successfull RREP (over all RREP)		:	%f\n", 	(double) nb_rrep_received / nb_rrep_transmitted );
							fprintf(file, "Percentage of Successfull RREP (over all RREQ)		:	%f\n", 	(double) nb_rrep_received / stats_nb_rreq );
							fprintf(file, "Average Delay before receiveing the RREP			:	%f\n", 		(double) average_delay_for_rrep / nb_rrep_received );
							fprintf(file, "Average Number of Retransmissions along a RREP		:	%f\n", 	(double) average_nb_retransmissions_rrep / nb_rrep_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rrep / nb_rrep_received  );
							fprintf(file, "\n");
							
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                          ENERGY                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Average Sleeping Time per node				:	%f\n", 			(double) somom_sleeping_total / nb_nodes  );
							fprintf(file, "Average Sleeping Time per authorized node			:	%f\n", 	(double) somom_sleeping_total / (nb_nodes * ratio_of_sleeping_nodes) );
							fprintf(file, "Ratio of Sleeping Time for authorized nodes		:	%f\n", 		(double) somom_sleeping_total / (nb_nodes * ratio_of_sleeping_nodes * op_sim_time())  );
							fprintf(file, "\n");
								
								
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                   Network Control                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
					
							fprintf(file, "--> Average Values per node, per second \n");
							fprintf(file, "Data									:	%f\n", 				(double) nb_pk_somom_data_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Data Retransmissions						:	%f\n", 			(double) nb_pk_somom_data_retransmission_total			/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Route Request							:	%f\n", 			(double) nb_pk_somom_rreq_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Route Reply								:	%f\n", 			(double) nb_pk_somom_rrep_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Route Reply Retransmissions					:	%f\n", 		(double) nb_pk_somom_rrep_retransmission_total			/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Route Update							:	%f\n", 				(double) nb_pk_somom_rup_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Route delete							:	%f\n", 				(double) nb_pk_somom_rdel_total							/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Unicast Acks							:	%f\n", 				(double) nb_pk_somom_ack_total					/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 			(double) (nb_pk_somom_data_total+nb_pk_somom_data_retransmission_total+nb_pk_somom_rreq_total+nb_pk_somom_rrep_total+nb_pk_somom_rrep_retransmission_total+nb_pk_somom_rup_total+nb_pk_somom_rdel_total+nb_pk_somom_ack_total)/((op_sim_time()-TIME_INIT_MAC) * nb_nodes));
							fprintf(file, "\n\n");
							
							fclose(file);
						
						}
				}


			/** state (ENDSIM) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "ENDSIM", "somom_process () [ENDSIM exit execs]")
				{
				}


			/** state (ENDSIM) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "ENDSIM", "idle")
				/*---------------------------------------------------------*/



			/** state (RET_UNICAST) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "RET_UNICAST", "somom_process () [RET_UNICAST enter execs]")
				{
				//retransmissions of all not acknowledged entries
					ack_couple*		couple;
					//Control
					char			msg [200];
					int				i;
					double			older_entry;
					//Random delay before transmitting
					double			delay;
					//Info for/from the packet
					Packet*			pk_dest;
					int				pk_type;
					int				pk_id;
					int				stat_id;
					int				address_final;
					int				address_src_init;
				
				
					//Older entry variable contains the time for which we must schedule an interuption
					older_entry = -1;
					//If the ack table is empty, we don't treat it ....
					if (op_prg_list_size(ack_table)!=0)
						{
							//For each entry
							for (i=op_prg_list_size(ack_table)-1 ; i>=0 ; i--)
								{
									//gets the entry
									couple = (ack_couple*) op_prg_list_access (ack_table, i);
				
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
													//If it is a data packet, sends a route_delete (the route seems broken)
													if (pk_type == DATA_PK_TYPE)
														send_route_delete(address_final);								
												
													//Remove it in the retransmission list	
													couple = NULL;
													op_prg_list_remove (ack_table , i);
													free(couple);
												}
											//if (couple->nb_retry < MAX_NB_RETRIES_UNICAST_ACKS)
											else if (couple->timeout <= op_sim_time())
												{
													op_pk_nfd_get(couple->pkptr, "STAT_ID",&stat_id);
												
													//retransmission
													couple->timeout = op_sim_time() + TIMEOUT_UNICAST_ACK;
													delay 			= op_dist_uniform(0.005);
													somom_pk_retransmit_delayed (op_pk_copy(couple->pkptr) , delay);			
														
													//Stats of nb of retransmissions
													switch (pk_type)
														{
															case DATA_PK_TYPE :
																stats_data_pk [stat_id].nb_retry++;
																if (1)//DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		data_debug (msg);
																	}
															break;
															case RREP_PK_TYPE :
																stats_rreq [stat_id].rrep_nb_retry++;
																if (1)//DEBUG>1)
																	{
																		sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address, couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
																		rrep_debug (msg);
																	}
															break;
															default:
																sprintf(msg, "This packet type (%d) is not destined to be acknowledged\n",pk_type);
																printf(msg);
																common_debug(msg);
															break;
														}
															
													couple->nb_retry++;							
													
													//DEBUG
													if (DEBUG>1)
														{
															sprintf(msg, "RETRANSMISSION : %d retransmits packet to %d with pk_id %d (stat_id %d) and currently %d retransmissions at %f\n", my_address , couple->dest , couple->pk_id , stat_id , couple->nb_retry+1 , op_sim_time()+delay);
															common_debug (msg);
															node_debug (msg);
														}							
												}
				
											//Test for max nb retransmissions
											if (couple->nb_retry + 1 >= MAX_NB_RETRIES_UNICAST_ACKS)
												{
													//If it is a data packet, sends a route_delete (the route seems broken)
													if ((pk_type == DATA_PK_TYPE) && (is_in_localization_table(address_final)))
														{
														//	delete_localization_entry(address_final);
														//	send_route_delete(address_final);
														}
													sprintf(msg, "RETRANSMISSION : %d exceeds the maximal number of retransmissions to %d at %f, We delete the entry in the ack table\n" , my_address , couple->dest , op_sim_time());
													op_prg_list_remove (ack_table , i);
													free(couple);
												}
											else
												couple->nb_retry++;							
										}
									if ((couple->timeout < older_entry) || (older_entry==-1))
										older_entry = couple->timeout;
								}
				
							//The next verification
							if (older_entry != -1)
								op_intrpt_schedule_self (older_entry , UNICAST_RETRANSMISSIONS_CODE);
							
				
							/*//The next verification
							if (older_entry != -1)
								op_intrpt_schedule_self (older_entry , UNICAST_RETRANSMISSIONS_CODE);
							*/
						}
				
				
				}


			/** state (RET_UNICAST) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "RET_UNICAST", "somom_process () [RET_UNICAST exit execs]")
				{
				}


			/** state (RET_UNICAST) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "RET_UNICAST", "idle")
				/*---------------------------------------------------------*/



			/** state (SEND_UPDATE) enter executives **/
			FSM_STATE_ENTER_FORCED (8, state8_enter_exec, "SEND_UPDATE", "somom_process () [SEND_UPDATE enter execs]")
				{
				/*char 		msg[150];
				double		tmp1, tmp2;
				Boolean		is_in_communication;
				Boolean		is_route_update_required;
				
				
				is_in_communication			= (communication_info.last_time_useful >= op_sim_time() - TIMEOUT_COMMUNICATION) || (communication_info.is_important);
				is_route_update_required	= (communication_info.last_time_update <= op_sim_time() - TIMEOUT_ROUTE_UPDATE) || (communication_info.is_important);
				
				
				if (is_in_communication)
					{
						if (is_route_update_required)
							send_route_update();
						
						//I am a communicating / Important Node --> Next Send Update
						if (!is_AP)
							op_intrpt_schedule_self (communication_info.last_time_update + TIMEOUT_ROUTE_UPDATE + 0.001, SEND_UPDATE_CODE);
					}
				//I am not important -> No Send_Update (but must Schedule the next verification)
				else
					op_intrpt_schedule_self (op_sim_time() + TIMEOUT_ROUTE_UPDATE, SEND_UPDATE_CODE);
				
				*/
				}


			/** state (SEND_UPDATE) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "SEND_UPDATE", "somom_process () [SEND_UPDATE exit execs]")
				{
				}


			/** state (SEND_UPDATE) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "SEND_UPDATE", "idle")
				/*---------------------------------------------------------*/



			/** state (STATE_CHANGED) enter executives **/
			FSM_STATE_ENTER_FORCED (9, state9_enter_exec, "STATE_CHANGED", "somom_process () [STATE_CHANGED enter execs]")
				{
				/* Code to execute when a DOMINATOR has a new state */
				
				
				
				//printf("Réception de l'interruption state changed\n");
				}


			/** state (STATE_CHANGED) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "STATE_CHANGED", "somom_process () [STATE_CHANGED exit execs]")
				{
				}


			/** state (STATE_CHANGED) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "STATE_CHANGED", "idle")
				/*---------------------------------------------------------*/



			/** state (SON_LOST) enter executives **/
			FSM_STATE_ENTER_FORCED (10, state10_enter_exec, "SON_LOST", "somom_process () [SON_LOST enter execs]")
				{
				/////////////////////////////////////////////////
				//
				// I lost one of my sons :
				//  Must I send a Route Delete to my parent ?
				//
				/////////////////////////////////////////////////
				
				int 		next_hop = -1;
				int 		src;
				Packet 		*pk;
				int			son_lost;
				int			*son_tmp;
				char	 	msg[200];
				
				
				//the child which is lost
				son_tmp	 = op_ima_obj_svar_get(cdcl_process_id , "last_son_lost");
				son_lost = *son_tmp;
				
				
				//Create a new formated route_delete
				pk = generate_route_delete();
				
				if (DEBUG>1)
					{
						sprintf(msg, "INIT : %d sends a route_delete for its son %d at %f\n", my_address , son_lost , op_sim_time());
						rdel_debug(msg);
					}
				
				//if no broken route must be advertised -> nothing to do
				if(! fill_route_delete(pk , son_lost))
					op_pk_destroy(pk);
				//Else, we send it !
				else
					{
						next_hop = get_relay_to_internet();
						op_pk_nfd_set(pk , "DEST" , next_hop);
				
						if(next_hop == -1)
							{
								sprintf(msg,"SON_LOST : %d can't find relay to Internet\n" , my_address);
								printf(msg);
								common_debug(msg);
							}
						else if(!is_AP)
							somom_pk_send(pk);						
					}
				}


			/** state (SON_LOST) exit executives **/
			FSM_STATE_EXIT_FORCED (10, "SON_LOST", "somom_process () [SON_LOST exit execs]")
				{
				}


			/** state (SON_LOST) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "SON_LOST", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,somom_process)
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
somom_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (somom_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (somom_process)",
			sizeof (somom_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((somom_process_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
somom_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
somom_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (somom_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in somom_process_svar function. */
#undef neighbour_table
#undef my_cds
#undef is_AP
#undef localization_table
#undef data_pk_buffer
#undef my_address
#undef received_stat_table
#undef sent_stat_table
#undef my_stat_id
#undef ack_table
#undef DEBUG
#undef rreq_pk_buffer
#undef current_id
#undef nb_connections
#undef intern_com_ratio
#undef data_pk_size
#undef communication_info
#undef cdcl_process_id
#undef paging_buffer
#undef paging_routing_table
#undef is_paging_master
#undef is_sleeping_authorized



void
somom_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	somom_process_state		*prs_ptr;

	FIN (somom_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (somom_process_state *)gen_ptr;

	if (strcmp ("neighbour_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->neighbour_table);
		FOUT;
		}
	if (strcmp ("my_cds" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_cds);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("localization_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->localization_table);
		FOUT;
		}
	if (strcmp ("data_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->data_pk_buffer);
		FOUT;
		}
	if (strcmp ("my_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_address);
		FOUT;
		}
	if (strcmp ("received_stat_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->received_stat_table);
		FOUT;
		}
	if (strcmp ("sent_stat_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->sent_stat_table);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("DEBUG" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DEBUG);
		FOUT;
		}
	if (strcmp ("rreq_pk_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->rreq_pk_buffer);
		FOUT;
		}
	if (strcmp ("current_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->current_id);
		FOUT;
		}
	if (strcmp ("nb_connections" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->nb_connections);
		FOUT;
		}
	if (strcmp ("intern_com_ratio" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->intern_com_ratio);
		FOUT;
		}
	if (strcmp ("data_pk_size" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->data_pk_size);
		FOUT;
		}
	if (strcmp ("communication_info" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->communication_info);
		FOUT;
		}
	if (strcmp ("cdcl_process_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->cdcl_process_id);
		FOUT;
		}
	if (strcmp ("paging_buffer" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->paging_buffer);
		FOUT;
		}
	if (strcmp ("paging_routing_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->paging_routing_table);
		FOUT;
		}
	if (strcmp ("is_paging_master" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_paging_master);
		FOUT;
		}
	if (strcmp ("is_sleeping_authorized" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_sleeping_authorized);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

