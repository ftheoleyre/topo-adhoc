/* Process model C form file: aodv_process.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char aodv_process_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 43298794 43298794 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                 ";
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

#include    <ip_addr_v4.h>
#include	<ip_rte_v4.h>
#include	<ip_cmn_rte_table.h>
#include 	<ip_rte_support.h>

#include	<udp_api.h>

#include	<oms_pr.h>
#include	<oms_stat_support.h>

#include	<stdlib.h>
#include	<stdio.h>
#include	<assert.h>
#include	<math.h>

//#include	"aodv_stats.h"




//---------------------------------------
//	
//				STATISTICS
//
//---------------------------------------


#define		TIME_BEGIN_STATS			60.0

//-------- DEBUG --------

#define		LOW							1
#define		MEDIUM						1
#define		HIGH						2
#define		MAX							3

#define		DEBUG_DATA					0
#define		DEBUG_ROUTE					0
#define		DEBUG_ACK					0

#define		DEBUG						0

//-------- TOPOLOGY --------

#define		MAX_NETWORK_RADIUS			255


//-------- OPNET --------

#define		PROCESS_NAME				"aodv"



//------------- MOBILITY -------------

#define		LOW_SPEED					1	
#define		HIGH_SPEED					2



//------------- PACKETS -------------


#define		MAX_DATA_PK					1000000
#define		MAX_RREQ_PK					1000000
#define		MAX_RERR_PK					1000000



//------------- DATA -------------

#define		TIMEOUT_DATA_PK_IN_BUFFER	1.0


#define		TIMEOUT_ICI					2.0



//------------------------------------
//			 ENVIRONMENT
//------------------------------------



#define AODV_ROUTING_PROCESS_NAME		"aodv"

#define TIME_BEGIN_DATA					60.0											// sim time when to start emission of first data packet
#define PACKET_SIZE						config_pkt_size									// simulated packet size


#define STRM_FROM_HIGHER_LAYER			0
#define STRM_TO_HIGHER_LAYER			0
#define STRM_FROM_MAC_LAYER				1
#define STRM_TO_MAC_LAYER				1

#define PKT_FROM_HIGHER_LAYER_CODE		0
#define GENERATE_PKT_FLOW_CODE			1
#define TIMEOUT_ROUTE_DISCOVERY_CODE	10
#define TIMEOUT_ACK_CODE				11
#define SEND_HELLO_CODE					12

#define WLAN2AODV_ACK_CODE				20
#define WLAN2AODV_NACK_CODE				21

#define TIME_INIT_MAC				5.0		// time until when the MAC layer is assumed to be initialized

#define END_SIM						(op_intrpt_type() == OPC_INTRPT_ENDSIM)
#define PKT_FROM_HIGHER_LAYER		((op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code() == PKT_FROM_HIGHER_LAYER_CODE))
#define GENERATE_PKT_FLOW			(((op_intrpt_type() == OPC_INTRPT_SELF) || (op_intrpt_type() == OPC_INTRPT_REMOTE)) && (op_intrpt_code() == GENERATE_PKT_FLOW_CODE))
#define ACK_FROM_MAC_LAYER			(((op_intrpt_type() == OPC_INTRPT_SELF) || (op_intrpt_type() == OPC_INTRPT_REMOTE)) && (op_intrpt_code() == WLAN2AODV_ACK_CODE))
#define TIMEOUT_ROUTE_DISCOVERY		((op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code() == TIMEOUT_ROUTE_DISCOVERY_CODE))
#define TIMEOUT_ACK					((op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code() == TIMEOUT_ACK_CODE))
#define TIMEOUT_HELLO				((op_intrpt_type() == OPC_INTRPT_SELF) && (op_intrpt_code() == SEND_HELLO_CODE))

//#define PKT_FROM_HIGHER_LAYER		((op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm() == STRM_FROM_HIGHER_LAYER))
#define PKT_FROM_MAC_LAYER			((op_intrpt_type() == OPC_INTRPT_STRM) && (op_intrpt_strm() == STRM_FROM_MAC_LAYER))


//#define MYIPADDR					ip_support_address_from_node_id_get(op_id_self())
#define AODV_BROADCAST_ADDR			-1

#define AODV_NODE_TRAVERSAL_TIME	0.040											// node traversal time (s)
#define AODV_NET_DIAMETER			35												// net diameter
#define AODV_NET_TRAVERSAL_TIME		(2*AODV_NODE_TRAVERSAL_TIME*AODV_NET_DIAMETER)	// time to traverse the net (s)
#define AODV_ACTIVE_ROUTE_TIMEOUT	3.0												// lifetime of an active route (s)
#define AODV_PATH_DISCOVERY_TIME	(2*AODV_NET_TRAVERSAL_TIME)						// time for which a registered RREQ is considered to be valid (s)
#define AODV_MY_ROUTE_TIMEOUT		(2*AODV_ACTIVE_ROUTE_TIMEOUT)					// lifetime of a RREP
#define AODV_DELETE_PERIOD			(5*AODV_ACTIVE_ROUTE_TIMEOUT)					// time after which an invalid RTE is discarded (s) TODO: modifications necessary, see RFC
#define AODV_RREQ_RETRIES			5												// max. number of retries with full TTL (additional attempts)
#define AODV_TIMEOUT_BUFFER			2	// buffer for the RREP timeout (configurable)
#define AODV_TTL_START				1	// expanding ring search start radius
#define AODV_TTL_INCREMENT			2	// expanding ring search incrementation of radius
#define AODV_TTL_THRESHOLD			7	// expanding ring search last radius
#define AODV_RING_TRAVERSAL_TIME	(2*AODV_NODE_TRAVERSAL_TIME * (aodv_ttl_value + AODV_TIMEOUT_BUFFER))	// timeout for expanding ring search (s); aodv_ttl_value has to be defined locally!
#define AODV_NEXT_HOP_WAIT			(AODV_NODE_TRAVERSAL_TIME + 0.010)				// timeout for waiting of a ACK when unicasting a packet to a nearby node
#define AODV_ALLOWED_HELLO_LOSS		2
#define AODV_HELLO_INTERVAL			1.0


#define PKT_TYPE_RREQ				1
#define PKT_TYPE_RREP				2
#define PKT_TYPE_RERR				3
#define PKT_TYPE_RREP_ACK			4
#define PKT_TYPE_DATA				100
#define PKT_TYPE_UNICAST_ACK		101

#define AODV_DEBUG_RT				0		// debug route table
#define AODV_DEBUG_PRECISION		(1e-8)	// double precision to use when comparing double egality
#define AODV_DEBUG_LEVEL			0		// 0 = all messages, 100 = config/urgent messages, 101 = no messages

#define AODV_CONFIG_DESTONLY		0		// FALSE, if RREP from intermediate nodes are allowed
#define AODV_CONFIG_GRATUITOUS		1

extern int aodv_pkt_flow_count;				// current packet flow count
extern int aodv_node_count;					// number of nodes in the current network


typedef int				AodvT_Address;
typedef unsigned int	AodvT_SeqNo;
typedef double			AodvT_Time;


/** structure to maintain node specific data **/
typedef struct AodvT_nodeInfo 
	{
		AodvT_SeqNo seqNo;
		AodvT_SeqNo reqId;
	}
AodvT_nodeInfo;

/** route table entry **/
typedef struct AodvT_rte 
	{
		AodvT_Address 	destAddr; 				// address of destination node
		AodvT_SeqNo 	destSeqNo;				// destination sequence number
		BOOL 			destSeqNoValid;			// false, if destSeqNo unknown
		BOOL			routeValid;				// true, if route currently valid
		AodvT_Time 		lifetime;				// time stamp until which the entry is valid (current time + AODV_ACTIVE_ROUTE_TIMEOUT)
		AodvT_Address 	nextHopAddr;			// address of next hop to destination node
		int 			hopCount;				// last known hop count to destination (-1 if unknown)
		
		AodvT_Time 		lastRreq;				// time stamp of last RREQ sent
		int				lastTtl;				// last TTL for expanding ring search
		int				rreqRetries;			// number of RREQ retries with full TTL
		BOOL			routeDiscovery;			// TRUE, if route discovery is in progress
		Evhandle		routeDiscoveryTimeout;	// handle of timeout
		
		List*			precursors;				// list of precursors (entry type: AodvT_Address)
		List*			queuedPackets;			// packets to send to that node (entry type: AodvT_datapk_queue_entry*)
		BOOL			acknowledged;			// indicates if the last packet to that node had been acknowledged
	}
AodvT_rte;

/** table that contains all RREQs received within the last AODV_PATH_DISCOVERY_TIME seconds */
typedef struct AodvT_rreqte
	{
		AodvT_Address	originAddr;
		AodvT_SeqNo		rreqId;
		AodvT_Time		timeStamp;
	}
AodvT_rreqte;

/** entry of a queued data packet */
typedef struct AodvT_datapk_queue_entry
	{
		AodvT_Address	destAddr;
		int				packetSize;
		AodvT_Time		sendTime;
		int				stat_id;
	}
AodvT_datapk_queue_entry;

/** entry of aodv_ack_wait */
typedef struct AodvT_ack_wait_entry
	{
		AodvT_Address	destAddr;
		Evhandle		timeout;		// ACK timeout
		BOOL			pinged;			// true, if NEXT_HOP_WAIT expired and a RREQ/ping was sent
	}
AodvT_ack_wait_entry;

/** some stats */
typedef struct AodvT_stats
	{
		int pkRREQ;
		int pkRREP;
		int pkRERR;
		int pkRREP_ACK;
		int pkDataSent;
		int pkDataRecvd;
	}
AodvT_stats;





//----------------------------------------------------------------------
//						FUNCTION    PROTOTYPES
//----------------------------------------------------------------------





extern FILE* aodvOut;
extern FILE* aodvPkTrace;
extern int aodvUseCount;

void dbg_print(const int level, const char* fmt, ...);


//Packet transmissions
void 	aodv_pk_send_to_mac_delayed(Packet* pkt, AodvT_Address destAddr , double delay);
void 	aodv_pk_send_to_mac(Packet* pkt, AodvT_Address destAddr);






//----------------------------------------------------------------------
//						Structures For Acks
//----------------------------------------------------------------------

typedef struct{
	int			dest;
	int			pk_id;
	double 		timeout;
	short		nb_retry;
	short		nb_repairs;
	List*		exceptions;
	packet*		pkptr;	
} ack_couple;


//----------------------------------------------------------------------
//						Structures For ICI Management
//----------------------------------------------------------------------

//Multiple Ici (one for each packet)
typedef struct{
	Ici*	ici_ptr;
	double	timeout;
} struct_ici;


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
	char	route[50];
} struct_stats_data;




//RREQ/RREP PK
typedef struct{
	int			source;
	int			dest;
	double		rreq_time_emission;
	double		rreq_time_reception;
	int			rreq_nb_retry;
	int			rreq_hops;
	int			nb_rreps;
	double		rrep_time_emission;
	double		rrep_time_reception;
	int			rrep_hops;
	int			rrep_nb_retry;
} struct_stats_rreq;

//RERR PK
typedef struct{
	int			source;
	int			dest;
	double		time_emission;
	double		time_reception;
	int			hops;
	int			nb_retry;
} struct_stats_rerr;



//----------------------------------------------------------------------
//						    Data 	Packets		
//----------------------------------------------------------------------
struct_stats_data	stats_data_pk 	[MAX_DATA_PK];

int			stats_nb_data_pk 		= 0;





/*----------------------------------------------------------------------
					    RREQ / RREP 	Packets		
----------------------------------------------------------------------*/
struct_stats_rreq	stats_rreq 	[MAX_RREQ_PK];
struct_stats_rerr	stats_rerr 	[MAX_RERR_PK];

int			stats_nb_rreq 				= 0;
int			stats_nb_rerr 				= 0;


/*----------------------------------------------------------------------
							OVERHEAD
----------------------------------------------------------------------*/
//In packets

int			nb_routing_pk_ack_total 									= 0;
int			nb_routing_pk_data_total 									= 0;
int			nb_routing_pk_data_ack_total 								= 0;
int			nb_routing_pk_rreq_total 									= 0;
int			nb_routing_pk_rrep_total 									= 0;
int			nb_routing_pk_rerr_total 									= 0;

//In bits

int			nb_routing_bits_ack_total 									= 0;
int			nb_routing_bits_data_total 									= 0;
int			nb_routing_bits_data_ack_total 								= 0;
int			nb_routing_bits_rreq_total 									= 0;
int			nb_routing_bits_rrep_total 									= 0;
int			nb_routing_bits_rerr_total 									= 0;





/*----------------------------------------------------------------------
							ENVIRONMENT
----------------------------------------------------------------------*/


// CONTROL
//double	simulation_duration	= 0;
int		nb_nodes					= 0;
int		nb_aps						= 0;
int		nb_wireless_routers			= 0;
int		nb_nodes_expected 			= 0;
int		nb_aps_expected				= 0;

int		begin_time_for_filenames	= 0;

//MOBILITY

int		nb_loc_low_speed_nodes		= 0;
int		nb_loc_high_speed_nodes		= 0;




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
	AodvT_Address	          		aodv_myAddr;
	AodvT_nodeInfo	         		aodv_myInfo;
	List*	                  		aodv_RT;
	List*	                  		aodv_RREQs;
	AodvT_stats	            		aodv_stats;
	List*	                  		aodv_ack_wait;
	BOOL	                   		aodv_config_wlan_ack;
	BOOL	                   		aodv_config_wlan_promiscuous_mode;
	BOOL	                   		aodv_config_passive_ack;
	BOOL	                   		aodv_config_hellos;
	Ici*	                   		aodv_flowgen_ici;
	BOOL	                   		bc_during_hello_interval;
	int	                    		my_stat_id;
	BOOL	                   		is_AP;
	List*	                  		ack_table;
	int	                    		DATA_PK_SIZE;
	double	                 		INTERARRIVAL_DATA_PK;
	int	                    		NB_PK_PER_FLOW;
	int	                    		NB_CONNECTIONS;
	List*	                  		ici_list;
	} aodv_process_state;

#define pr_state_ptr            		((aodv_process_state*) SimI_Mod_State_Ptr)
#define aodv_myAddr             		pr_state_ptr->aodv_myAddr
#define aodv_myInfo             		pr_state_ptr->aodv_myInfo
#define aodv_RT                 		pr_state_ptr->aodv_RT
#define aodv_RREQs              		pr_state_ptr->aodv_RREQs
#define aodv_stats              		pr_state_ptr->aodv_stats
#define aodv_ack_wait           		pr_state_ptr->aodv_ack_wait
#define aodv_config_wlan_ack    		pr_state_ptr->aodv_config_wlan_ack
#define aodv_config_wlan_promiscuous_mode		pr_state_ptr->aodv_config_wlan_promiscuous_mode
#define aodv_config_passive_ack 		pr_state_ptr->aodv_config_passive_ack
#define aodv_config_hellos      		pr_state_ptr->aodv_config_hellos
#define aodv_flowgen_ici        		pr_state_ptr->aodv_flowgen_ici
#define bc_during_hello_interval		pr_state_ptr->bc_during_hello_interval
#define my_stat_id              		pr_state_ptr->my_stat_id
#define is_AP                   		pr_state_ptr->is_AP
#define ack_table               		pr_state_ptr->ack_table
#define DATA_PK_SIZE            		pr_state_ptr->DATA_PK_SIZE
#define INTERARRIVAL_DATA_PK    		pr_state_ptr->INTERARRIVAL_DATA_PK
#define NB_PK_PER_FLOW          		pr_state_ptr->NB_PK_PER_FLOW
#define NB_CONNECTIONS          		pr_state_ptr->NB_CONNECTIONS
#define ici_list                		pr_state_ptr->ici_list

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	aodv_process_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
//#include "aodv_stats.h"
//#include "stdio.h"


/*-----------------------------------------------------------------------------------------------

								FUNCTION DECLARATIONS

-----------------------------------------------------------------------------------------------*/



int aodv_pkt_flow_count = 0;
int aodv_node_count = 0;



void aodv_rte_precursors_remove(AodvT_rte* rte, AodvT_Address precursorAddr);
AodvT_ack_wait_entry* aodv_ack_wait_get(AodvT_Address destAddr);
void aodv_pk_data_send(AodvT_Address destAddr , int id);
void aodv_initiate_rreq(AodvT_rte* rte, int aodv_ttl_value);








/*-----------------------------------------------------------------------------------------------

								ICI MANAGEMENT 	FOR MAC LAYER

-----------------------------------------------------------------------------------------------*/



//Add a new Ici in the ici_list
Ici* add_in_ici_list(){
	struct_ici*		entry;
	
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_ici*) op_prg_mem_alloc ( sizeof (struct_ici));
	
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
	
	if (ici_list == NULL)
		op_sim_end("We have an error :" , "the ici list is a null list" , "please initialize it","");

	//If the list is empty
	if (op_prg_list_size(ici_list)==0)
		return;
	
	//For each entry
	while (i< op_prg_list_size(ici_list))
		{
			entry = (struct_ici*) op_prg_list_access (ici_list, i);
			
			//We delete the entry (which is timeouted)
			if (entry->timeout < op_sim_time())
				{
					op_prg_list_remove ( ici_list , i);
					free(entry);
				}
			else
				i++;
		}
}



/*-----------------------------------------------------------------------------------------------

								DEBUG

-----------------------------------------------------------------------------------------------*/
FILE* aodvOut = 0;		// debug file
int aodvUseCount = 0;	// use count of file

void aodv_rte_maintain();




void sav(const char* fmt, ...){
	FILE	*pfile;
	va_list argptr;
	
	printf("deb\n");
	
	pfile = fopen("results_aodv/aodv_test.txt" , "a");
	printf("deb2\n");

	
	va_start(argptr, fmt);
	printf("deb3\n");
		
	//fprintf(pfile, "[%8.4fs,%2.1i] ", op_sim_time(), aodv_myAddr);	
	vfprintf(pfile, fmt, argptr);     
	printf("deb4\n");
		
	fflush(0);	

	va_end(argptr);

	printf("fin\n");
}

void debug_test(char *msg){
	FILE	*pfile;
	
	pfile = fopen("results_aodv/aodv_test.txt" , "a");
	fprintf(pfile, msg);
	fclose(pfile);
}


/*-----------------------------------------------------------------------------------------------

								AODV by Denis (after some modificaitons)

-----------------------------------------------------------------------------------------------*/




// Print all debug messages in one file
void dbg_print(const int level, const char* fmt, ...){	
	if (DEBUG > 100)
		{
			va_list argptr;
			va_start(argptr, fmt);
			
			if (level >= AODV_DEBUG_LEVEL)
				{
					fprintf(aodvOut, "[%8.4fs,%2.1i] ", op_sim_time(), aodv_myAddr);	
					vfprintf(aodvOut, fmt, argptr);     
		
					fflush(0);	
				}
			va_end(argptr);
		}
}




/* *** Route table management ************************************************************************** */

/** helper proc: comparison function for route table entries */
int aodv_rte_compare_proc(const AodvT_rte* e1, const AodvT_rte* e2)
	{
		if (e1->destAddr == e2->destAddr)
			return 0;
		else if (e1->destAddr < e2->destAddr) 
			return 1;
		else
			return -1;
	}

/** helper proc: debug RT */
void aodv_rte_dbg_print(const int level)
	{
		char	msg[1000];
		int 		i, j;
		AodvT_rte	* rte;
		
		if (level >= AODV_DEBUG_LEVEL)
			{
				char s[512];
				
				for (i = 0; i < op_prg_list_size(aodv_RT); i++)
					{
						rte = op_prg_list_access(aodv_RT, i);
		
						s[0] = '\0';
						for (j = 0; j < op_prg_list_size(rte->precursors); j++)
							{
								sprintf(s, "%s %i", s, *((int*)op_prg_list_access(rte->precursors, j)));
							}
				
						if ((DEBUG) && (level > 100000))
							{
								sprintf(msg , "RTE: %d: seqNo %d, seqNoValid %d, routeValid %d, routeDiscovery %d, lifetime %1.4fs, nextHop %d, hopCount %d, lastRreq %1.4fs, precursors [%s]\n", 
									rte->destAddr, rte->destSeqNo, rte->destSeqNoValid, rte->routeValid, rte->routeDiscovery, rte->lifetime, rte->nextHopAddr, rte->hopCount, rte->lastRreq, s);
								debug_test(msg);
							}
					}
			}
	}

/** helper proc: return a route table entry for a node or NULL */
AodvT_rte* aodv_rte_get(AodvT_Address destAddr)
	{
		AodvT_rte tmpRte;
		AodvT_rte* res;
		int low = 0;
		int high = 0;
		
	   	assert(destAddr > 0 && destAddr <= aodv_node_count);
		
		if (AODV_DEBUG_RT)
			{	
				dbg_print(100, "aodv_rte_get(%d)\n", destAddr);
				aodv_rte_dbg_print(100);
			}
		
		tmpRte.destAddr = destAddr;
		
		res = op_prg_list_elem_find(aodv_RT, 
									aodv_rte_compare_proc, 
									&tmpRte,
									&low,
									&high);

		if (res && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_RT));
				fflush(0);
				assert(0);
			}
		
		return res;
	}


/** helper proc: create a route table entry for a node */
AodvT_rte* aodv_rte_create(AodvT_Address destAddr)
	{
		AodvT_rte* rte = (AodvT_rte*) op_prg_mem_alloc(sizeof(AodvT_rte));
		
		memset(rte, 0, sizeof(AodvT_rte));
		
		if (destAddr == aodv_myAddr)
			assert(0);

		
		if (AODV_DEBUG_RT)
			{
				dbg_print(100, "aodv_rte_create(%d)\n", destAddr);
				aodv_rte_dbg_print(100);
			}
		
		rte->destAddr = destAddr;
		rte->destSeqNo = 0;
		rte->destSeqNoValid = FALSE;
		rte->routeValid = FALSE;
		rte->lifetime = op_sim_time() + AODV_DELETE_PERIOD;
		rte->nextHopAddr = 0;
		rte->hopCount = 0;
		rte->lastRreq = 0.0; //op_sim_time();
		rte->lastTtl = 0;
		rte->rreqRetries = -1;
		rte->routeDiscovery = FALSE;
		rte->precursors = op_prg_list_create();
		rte->queuedPackets = op_prg_list_create();
		rte->acknowledged = TRUE;	// first packet may be sent without a prior ACK
		
		op_prg_list_insert_sorted(aodv_RT, rte, aodv_rte_compare_proc);

		if (AODV_DEBUG_RT)
			{
				dbg_print(100, "aodv_rte_create(): destination %d added\n", destAddr);
				aodv_rte_dbg_print(100);
			}		
		
		return rte;
	}

/** helper proc: remove a route table entry for a node */
void aodv_rte_remove(AodvT_Address destAddr)
	{
		AodvT_rte tmpRte;
		AodvT_rte* res;
		int low = 0;
		int high = 0;
		AodvT_Address* addr;
		int i;
		
		if (AODV_DEBUG_RT)
			{
				dbg_print(100, "aodv_rte_remove(%d)\n", destAddr);
				aodv_rte_dbg_print(100);
			}
		
		tmpRte.destAddr = destAddr;
		
		res = op_prg_list_elem_find(aodv_RT, 
									aodv_rte_compare_proc, 
									&tmpRte,
									&low,
									&high);
		
		if (res && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_RT));
				fflush(0);
				assert(0);
			}
		
		if (res) 
			{
   				assert(op_prg_list_remove(aodv_RT, low) == res);
				
				assert(op_prg_list_size(res->queuedPackets) == 0);
				op_prg_list_free(res->queuedPackets);
				
				while (op_prg_list_size(res->precursors) > 0)
					{
						addr = op_prg_list_remove(res->precursors, OPC_LISTPOS_HEAD);
						assert(addr != NULL);
						op_prg_mem_free(addr);
					}
				op_prg_list_free(res->precursors);
				res->precursors = NULL;
				
				// remove us from other precursor lists
				for (i = 0; i < op_prg_list_size(aodv_RT); i++)
					{
						AodvT_rte* rte;
						
						rte = op_prg_list_access(aodv_RT, i);
						if (rte != res)
							{
								aodv_rte_precursors_remove(rte, destAddr);
							}
					}
				
				op_prg_mem_free(res);
			}
	}

void aodv_rte_update_lifetime(AodvT_rte* rte, double lifetime)
	{
		rte->lifetime = lifetime;
		//dbg_print(1, "Updated lifetime of RTE for node %i (lifetime %1.8f, routeValid %i)\n", 
		//	rte->destAddr, rte->lifetime, rte->routeValid);

		assert(rte->lifetime - op_sim_time() >= 0);
		if (!(
				(rte->routeValid && (rte->lifetime - op_sim_time() - AODV_ALLOWED_HELLO_LOSS*AODV_HELLO_INTERVAL <= AODV_DEBUG_PRECISION)) ||
				//(rte->routeValid && (rte->lifetime - op_sim_time() <= AODV_ACTIVE_ROUTE_TIMEOUT)) ||
				(rte->routeValid && (rte->lifetime - op_sim_time() - AODV_MY_ROUTE_TIMEOUT < AODV_DEBUG_PRECISION)) ||
				(!rte->routeValid && !rte->routeDiscovery && (rte->lifetime - op_sim_time() - AODV_DELETE_PERIOD < AODV_DEBUG_PRECISION)) ||
				(rte->routeDiscovery && (rte->lifetime - op_sim_time() - (1<<6)*AODV_NET_TRAVERSAL_TIME < AODV_DEBUG_PRECISION))
			))
			{
				aodv_rte_dbg_print(100);
				assert(0);
			}
		
	}

/** mark a RTE as active, cancelling timers if necessary */
void aodv_rte_activate_route(AodvT_rte* rte)
	{
		assert(NULL != rte);
		
		rte->routeValid = TRUE;
		aodv_rte_update_lifetime(rte, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
		if (rte->routeDiscovery)
			{
				rte->routeDiscovery = FALSE;
				assert(OPC_COMPCODE_SUCCESS == op_ev_cancel(rte->routeDiscoveryTimeout));
				
				dbg_print(1, "route discovery timeout for node %i canceled\n", rte->destAddr);
			}
	}

/** mark a RTE as invalid */
void aodv_rte_invalidate_route(AodvT_rte* rte)
	{
		int i;
		AodvT_rte* rte2;
	
		assert(NULL != rte);
		if (!rte->routeValid)
			{
				// don't touch it
				return;
			}
		
		assert(!rte->routeDiscovery);
		rte->routeValid = FALSE;
		aodv_rte_update_lifetime(rte, op_sim_time() + AODV_DELETE_PERIOD);
		
		// do we have queued packets for that node?
		if (op_prg_list_size(rte->queuedPackets) > 0)
			{
				// re-initiate RREQ
				aodv_initiate_rreq(rte, rte->hopCount + AODV_TTL_INCREMENT);
			}
		
		// invalidate all entries that are using this node as a next hop
		for (i = 0; i < op_prg_list_size(aodv_RT); i++)
			{
				rte2 = op_prg_list_access(aodv_RT, i);
				if (rte2->routeValid &&
					(rte2->destAddr != rte->destAddr) && 
					(rte2->nextHopAddr == rte->destAddr))
					{
						rte2->routeValid = FALSE;
						aodv_rte_update_lifetime(rte2, op_sim_time() + AODV_DELETE_PERIOD);
						
						// do we have queued packets for that node?
						if (op_prg_list_size(rte2->queuedPackets) > 0)
							{
								// re-initiate RREQ
								if (!rte2->routeDiscovery)
									{
										aodv_initiate_rreq(rte2, rte2->hopCount + AODV_TTL_INCREMENT);
									}
							}
					}
			}		
	}

int aodv_rte_precursors_compare_proc(const AodvT_Address* e1, const AodvT_Address* e2)
	{
		assert(e1 != NULL && e2 != NULL);
		
		if (*e1 == *e2)
			return 0;
		else if (*e1 < *e2) 
			return 1;
		else
			return -1;
	}

void aodv_rte_precursors_dbg_print(AodvT_rte* rte)
	{
		char s[256];
		int i;
		
		s[0] = '\0';
		
//		dbg_print(1, "Precursor list size: %i\n", op_prg_list_size(rte->precursors));
		
		for (i = 0; i < op_prg_list_size(rte->precursors); i++)
			{
				sprintf(s, "%s %i", s, *((int*)op_prg_list_access(rte->precursors, i)));
			}
		
		dbg_print(100, "Precursors:%s\n", s);
	}

void aodv_rte_precursors_add(AodvT_rte* rte, AodvT_Address precursorAddr)
	{
		int low, high;
		AodvT_Address* addr;
		
		assert(rte != NULL && rte->precursors != NULL);
		
//		dbg_print(1, "aodv_rte_precursors_add(rte->destAddr %i, precursorAddr %i)\n", rte->destAddr, precursorAddr);
//		aodv_rte_precursors_dbg_print(rte);
		
		// ignore duplicates
		addr = op_prg_list_elem_find(rte->precursors, 
									 aodv_rte_precursors_compare_proc, 
									 &precursorAddr,
									 &low,
									 &high);
		if (addr == OPC_NIL)
			{
				addr = op_prg_mem_alloc(sizeof(AodvT_Address));
				assert(addr != OPC_NIL);
				*addr = precursorAddr;
				op_prg_list_insert_sorted(rte->precursors, addr, aodv_rte_precursors_compare_proc);
			}
		else
			{
				assert(low == high);
			}
	}

BOOL aodv_rte_precursors_is_precursor(AodvT_rte* rte, AodvT_Address precursorAddr)
	{
		int low, high;
		AodvT_Address* addr;
		
		assert(rte != NULL && rte->precursors != NULL);
		
//		dbg_print(1, "aodv_rte_precursors_is_precursor(rte->destAddr %i, precursorAddr %i)\n", rte->destAddr, precursorAddr);
//		aodv_rte_precursors_dbg_print(rte);
		
		// ignore duplicates
		addr = op_prg_list_elem_find(rte->precursors, 
									 aodv_rte_precursors_compare_proc, 
									 &precursorAddr,
									 &low,
									 &high);
		
		return (addr != OPC_NIL);
	}

void aodv_rte_precursors_remove(AodvT_rte* rte, AodvT_Address precursorAddr)
	{
		int low, high;
		AodvT_Address* addr;
		
		assert(rte != NULL && rte->precursors != NULL);
		
//		dbg_print(1, "aodv_rte_precursors_remove(rte->destAddr %i, precursorAddr %i)\n", rte->destAddr, precursorAddr);
//		aodv_rte_precursors_dbg_print(rte);
		
		// ignore absence of entry
		addr = op_prg_list_elem_find(rte->precursors, 
									 aodv_rte_precursors_compare_proc, 
									 &precursorAddr,
									 &low,
									 &high);
		if (addr != OPC_NIL)
			{
				assert(low == high);
				assert(*addr == precursorAddr);
				assert(op_prg_list_remove(rte->precursors, low) == addr);
				op_prg_mem_free(addr);
			}
	}



/* *** RREQs table management ************************************************************************** */
	
/** helper proc: comparison function for RREQs table entries */
int aodv_rreqs_compare_proc(const AodvT_rreqte* e1, const AodvT_rreqte* e2)
	{
		if (e1->originAddr == e2->originAddr)
			if (e1->rreqId == e2->rreqId)
				return 0;
			else if (e1->rreqId < e2->rreqId)
				return 1;
			else
				return -1;
		else if (e1->originAddr < e2->originAddr)
			return 1;
		else
			return -1;
	}

/** helper proc: return a RREQs table entry for a node or NULL */
AodvT_rreqte* aodv_rreqs_get(AodvT_Address originAddr, AodvT_SeqNo rreqId)
	{
		AodvT_rreqte tmpRreqte;
		AodvT_rreqte* res;
		int low = 0;
		int high = 0;
		
		tmpRreqte.originAddr = originAddr;
		tmpRreqte.rreqId = rreqId;
		
		res = op_prg_list_elem_find(aodv_RREQs, 
									aodv_rreqs_compare_proc, 
									&tmpRreqte,
									&low,
									&high);

		if (res && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_RREQs));
				fflush(0);
				assert(0);
			}
		
		return res;
	}


/** helper proc: create a RREQs table entry for a node */
AodvT_rreqte* aodv_rreqs_create(AodvT_Address originAddr, AodvT_SeqNo rreqId)
	{
		AodvT_rreqte* rreqte = (AodvT_rreqte*) op_prg_mem_alloc(sizeof(AodvT_rreqte));
		
		rreqte->originAddr = originAddr;
		rreqte->rreqId = rreqId;
		rreqte->timeStamp = op_sim_time();
		
		op_prg_list_insert_sorted(aodv_RREQs, rreqte, aodv_rreqs_compare_proc);

		return rreqte;
	}

/** helper proc: remove a RREQs table entry for a node */
void aodv_rreqs_remove(AodvT_Address originAddr, AodvT_SeqNo rreqId)
	{
		AodvT_rreqte tmpRreqte;
		AodvT_rreqte* res;
		int low = 0;
		int high = 0;
		
		tmpRreqte.originAddr = originAddr;
		tmpRreqte.rreqId = rreqId;
		
		res = op_prg_list_elem_find(aodv_RREQs, 
									aodv_rreqs_compare_proc, 
									&tmpRreqte,
									&low,
									&high);

		if (res && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_RREQs));
				fflush(0);
				assert(0);
			}
		
		assert(res);
		
		if (res)
			{
   				assert(op_prg_list_remove(aodv_RREQs, low) == res);
				op_prg_mem_free(res);
			}
	}

/** cleanup list of superfluous entries */
void aodv_rreqs_maintain()
	{
		int i;
		AodvT_rreqte* rreqte;
		
		i = 0;
		while (i < op_prg_list_size(aodv_RREQs))
			{
				rreqte = op_prg_list_access(aodv_RREQs, i);
				if (op_sim_time() - rreqte->timeStamp > AODV_PATH_DISCOVERY_TIME)
					{
						aodv_rreqs_remove(rreqte->originAddr, rreqte->rreqId);
					}
				else
					{
						i++;
					}
			}
	}

/* *** ACK wait table management *********************************************************************** */

AodvT_ack_wait_entry* aodv_ack_wait_create(AodvT_Address destAddr)
	{
		AodvT_ack_wait_entry* awe;
		
		assert(aodv_ack_wait_get(destAddr) == NULL);
		
		awe = (AodvT_ack_wait_entry*) op_prg_mem_alloc(sizeof(AodvT_ack_wait_entry));
		
		awe->destAddr = destAddr;
		awe->pinged = FALSE;
		awe->timeout = op_intrpt_schedule_self(op_sim_time() + AODV_NEXT_HOP_WAIT, TIMEOUT_ACK_CODE);
		
		op_prg_list_insert_sorted(aodv_ack_wait, awe, aodv_rte_compare_proc); // same compare proc as for RT!
		
		dbg_print(1, "Set ACK timeout for destAddr %i\n", destAddr);
		
		return awe;
	}

AodvT_ack_wait_entry* aodv_ack_wait_get(AodvT_Address destAddr)
	{
		AodvT_ack_wait_entry tmpAwe;
		AodvT_ack_wait_entry* awe;
		
		int low = 0;
		int high = 0;
		
		tmpAwe.destAddr = destAddr;
		
		awe = op_prg_list_elem_find(aodv_ack_wait, 	
									aodv_rte_compare_proc, 	// same compare proc as for RT!
									&tmpAwe,	
									&low,
									&high);

		if (awe && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_ack_wait));
				fflush(0);
				assert(0);
			}
		
		return awe;
	}

void aodv_ack_wait_remove(AodvT_Address destAddr, BOOL cancelTimeout)
	{
		AodvT_ack_wait_entry tmpAwe;
		AodvT_ack_wait_entry* awe;
		AodvT_rte* rte;
		
		int low = 0;
		int high = 0;
		
		assert(destAddr >= 0);
		
		tmpAwe.destAddr = destAddr;
		
		awe = op_prg_list_elem_find(aodv_ack_wait, 	
									aodv_rte_compare_proc, 	// same compare proc as for RT!
									&tmpAwe,	
									&low,
									&high);

		if (awe && (low != high))
			{
				dbg_print(100, "element more than once in list: low = %i, high = %i, size = %i\n", low, high, op_prg_list_size(aodv_ack_wait));
				fflush(0);
				assert(0);
			}
		
		if (awe)
			{
   				assert(op_prg_list_remove(aodv_ack_wait, low) == awe);
				
				if (cancelTimeout)
					{
						assert(OPC_COMPCODE_SUCCESS == op_ev_cancel(awe->timeout));
						dbg_print(1, "Canceled ACK timeout for destAddr %i\n", destAddr);
					}
				
				op_prg_mem_free(awe);
			}
		else
			{
				//dbg_print(1, "No ACK timeout for destAddr %i to remove\n", destAddr);
			}
		
		rte = aodv_rte_get(destAddr);
		if (rte != NULL)
			{
				rte->acknowledged = TRUE;
			}
	}



//Updates the statistics about overheads
void aodv_stats_about_overheads(Packet* pkt){
	int 	type , stat_id;
	
	
	//packet fields
	op_pk_nfd_get(pkt, "Type", 		&type);
	op_pk_nfd_get(pkt, "STAT_ID", 	&stat_id);	

	
	// some generic stats
	switch (type)
		{
			case PKT_TYPE_DATA:
				{
					if (op_sim_time() > TIME_BEGIN_DATA)
						{
							nb_routing_pk_data_total++;
							nb_routing_bits_data_total += op_pk_total_size_get(pkt);	
						}
					
					break;
				}
			case PKT_TYPE_RREQ:
				{
					if (op_sim_time() > TIME_BEGIN_DATA)
						{
							nb_routing_pk_rreq_total++;
							nb_routing_bits_rreq_total += op_pk_total_size_get(pkt);						
						}
					break;
				}
			case PKT_TYPE_RREP:
				{
					if (op_sim_time() > TIME_BEGIN_DATA)
						{
							nb_routing_pk_rrep_total++;
							nb_routing_bits_rrep_total += op_pk_total_size_get(pkt);						
						}
					break;
				}
			case PKT_TYPE_RERR:
				{
					if (op_sim_time() > TIME_BEGIN_DATA)
						{
							nb_routing_pk_rerr_total++;
							nb_routing_bits_rerr_total += op_pk_total_size_get(pkt);						
						}
					break;
				}
			default:
				{
					op_sim_end("unknown packet to send to the MAC layer", "","","");
					assert(0);
					break;
				}
		}

}



/* *** Packet send functions *************************************************************************** */

/** 
 * send a packet to the mac-layer 
 * 
 * @parm pkt		Packet pointer of packet to be sent
 * @parm destAddr	Next hop's address on the route
 */
void aodv_pk_send_to_mac(Packet* pkt, AodvT_Address destAddr){
	aodv_pk_send_to_mac_delayed(pkt, destAddr , 0);
}
	
void aodv_pk_send_to_mac_delayed(Packet* pkt, AodvT_Address destAddr , double delay)
	{	
		Ici* 	ici_ptr;
	
		int		stat_id;
		int 	type;
		
		BOOL expectAck = FALSE;
		AodvT_Address addr;
		
		if (!((destAddr == AODV_BROADCAST_ADDR) || (destAddr > 0 && destAddr <= aodv_node_count)))
			{
				printf("%d\n", destAddr);
				op_pk_print(pkt);
			}
		
		assert((destAddr == AODV_BROADCAST_ADDR) || (destAddr > 0 && destAddr <= aodv_node_count));
		
		op_pk_nfd_get(pkt, "Type", 		&type);
		op_pk_nfd_get(pkt, "STAT_ID", 	&stat_id);	
		
		
		
		// emulate data normally found in an IP header
		assert(OPC_COMPCODE_FAILURE != op_pk_nfd_set(pkt, "NextHop", destAddr));
		assert(OPC_COMPCODE_FAILURE != op_pk_nfd_set(pkt, "PrevHop", aodv_myAddr));
		
		
		
		//-----------------------------------
		// 
		//			Overheads
		//
		//-----------------------------------
	
		
		aodv_stats_about_overheads(pkt);
		
		
		//-----------------------------------
		// 
		//			ACKS
		//
		//-----------------------------------
		
		// should we expect an ACK?		
		if (!aodv_config_passive_ack)
			// we do not expect any ACK
			expectAck = FALSE;
		
		else if (aodv_config_wlan_ack)
			// we can expect an ACK for every packet that is not broadcasted
			expectAck = (destAddr != AODV_BROADCAST_ADDR);
		
		else if (aodv_config_wlan_promiscuous_mode)
				// we can expect an ACK only in certain cases
				switch (type)
					{
						case PKT_TYPE_RREQ:
							{
								// only unicast RREQs
								expectAck = (destAddr != AODV_BROADCAST_ADDR);
								break;
							}
						case PKT_TYPE_RREP:
							{
								// only RREPs that have to be forwarded by the next hop
								op_pk_nfd_get(pkt, "Origin_IPAddr", &addr);
								expectAck = (destAddr != addr);
								break;
							}
						case PKT_TYPE_RERR:
							{
								// never for RERRs
								expectAck = FALSE;
								break;
							}
						case PKT_TYPE_DATA:
							{
								// always for data packets (in the worst case, we have to send an unicast RREQ)
								expectAck = TRUE;
								break;
							}
						default:
							{
								assert(0);
								break;
							}
					}
		
		else
			{
				// here we are neither in promiscuous mode nor do we use layer-2-acks
				// so we do expect only for data packets an ack, probably through sending 
				// an unicast RREQ (this mode is NOT suggested)
				if (type == PKT_TYPE_DATA)
					expectAck = TRUE;
				else
					expectAck = FALSE;
			}
		
		
		
		//-----------------------------------
		// 
		//	TRANSMISSION TO MAC LAYER
		//
		//-----------------------------------

		//Ici
		ici_ptr = add_in_ici_list();
		op_ici_attr_set(ici_ptr,"dest_addr", destAddr);
		op_ici_install(ici_ptr);
	
		//Transmission
		op_pk_send_delayed(pkt, STRM_TO_MAC_LAYER , delay);
		
		
		if (destAddr == AODV_BROADCAST_ADDR)
			bc_during_hello_interval = TRUE;

		
		
		//-----------------------------------
		// 
		//			ACKS TIMEOUT
		//
		//-----------------------------------
		
		// set ACK timeout
		if (expectAck)
			{
				AodvT_ack_wait_entry* awe;
				AodvT_rte* rte;
				
				assert(destAddr != AODV_BROADCAST_ADDR);
				
				dbg_print(1, "EXPECT ACK\n");
				
				rte = aodv_rte_get(destAddr);
				if (!rte->routeValid)
					{	
						dbg_print(100, "destnode %i\n", destAddr);
						aodv_rte_dbg_print(100);
						assert(0);
					}
				rte->acknowledged = FALSE;
				
				awe = aodv_ack_wait_get(destAddr);
				if (NULL == awe)
					{
						aodv_ack_wait_create(destAddr);
					}
			}
	}

/**
 * send a data packet or queue it if there is no route
 */
void aodv_pk_data_send( AodvT_Address destAddr, int id)
	{		
		Packet* dataPkt;
	
		AodvT_rte* 	rte_d;
		AodvT_rte* 	rte_n;
		
		rte_d = aodv_rte_get(destAddr);
		assert(NULL != rte_d && rte_d->routeValid);
		
		rte_n = aodv_rte_get(rte_d->nextHopAddr);
		//assert(NULL != rte2 && rte2->routeValid);
		if (!(NULL != rte_n && rte_n->routeValid))
			{
				aodv_rte_dbg_print(1000000);
				fflush(0);
				//assert(0);
				
				dbg_print(1, "DATA: data packet not sent to node %i (incoherence in the routing table) \n", destAddr);
			}
		else
			{
				aodv_rte_update_lifetime(rte_d, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
				aodv_rte_update_lifetime(rte_n, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
		
				dataPkt = op_pk_create_fmt("aodv_data");
		
				op_pk_nfd_set(dataPkt, "Dest_IPAddr", 	destAddr);
				op_pk_nfd_set(dataPkt, "Origin_IPAddr", aodv_myAddr);
				op_pk_nfd_set(dataPkt, "PrevHop", 		aodv_myAddr);
				op_pk_nfd_set(dataPkt, "STAT_ID", 		id);
				op_pk_nfd_set(dataPkt, "TTL", 			MAX_NETWORK_RADIUS);
	
				//Pk Size
				op_pk_bulk_size_set(dataPkt , (int) op_dist_exponential( (double)DATA_PK_SIZE * 8)  );
		
				// stats		
				stats_data_pk 	[id].time_emission	= op_sim_time();
				stats_data_pk 	[id].pk_size		= op_pk_bulk_size_get(dataPkt);;		
		
				aodv_pk_send_to_mac(dataPkt, rte_d->nextHopAddr);
		
				dbg_print(1, "DATA: sent a data packet to node %i via node %i \n", destAddr, rte_d->nextHopAddr);
			}
	}
	
/** 
 * send route request RREQ 
 *
 * TODO: 
 * 		RREQ_RATELIMIT
 *
 * @parm destAddr		Address for which a route is requested
 * @parm ttl			Time to live (for expanding ring search)
 * @parm nextHopAddr	Address to which the RREQ is destined
 */
void aodv_pk_send_rreq_to_addr(AodvT_Address destAddr, int ttl, AodvT_Address nextHopAddr) 
	{	
		/*	6.3
			The Destination Sequence Number field in the RREQ message is the last
			known destination sequence number for this destination and is copied
			from the Destination Sequence Number field in the routing table.  If
			no sequence number is known, the unknown sequence number flag MUST be
			set.  The Originator Sequence Number in the RREQ message is the
			node's own sequence number, which is incremented prior to insertion
			in a RREQ.  The RREQ ID field is incremented by one from the last
			RREQ ID used by the current node.  Each node maintains only one RREQ
			ID.  The Hop Count field is set to zero.
		*/
	
		Packet* pkt;
		AodvT_rte* rte;
		
		int destOnly = AODV_CONFIG_DESTONLY;
		int gratuitous = AODV_CONFIG_GRATUITOUS;
			
			
		rte = aodv_rte_get(destAddr);
		assert(NULL != rte);
		
		rte->lastRreq = op_sim_time();
		
		pkt = op_pk_create_fmt("aodv_rreq");
		op_pk_nfd_set(pkt, "Origin_IPAddr", aodv_myAddr);
		op_pk_nfd_set(pkt, "Origin_SeqNo", ++aodv_myInfo.seqNo);
		op_pk_nfd_set(pkt, "RREQ_ID", ++aodv_myInfo.reqId);
		op_pk_nfd_set(pkt, "Dest_IPAddr", destAddr);
		
		op_pk_nfd_set(pkt, "PrevHop", aodv_myAddr);
		op_pk_nfd_set(pkt, "TTL", ttl); 
		
		if (rte->destSeqNoValid) {
			op_pk_nfd_set(pkt, "Dest_SeqNo", rte->destSeqNo);
		} else {
			op_pk_nfd_set(pkt, "U", 1); // destination seqNo unknown
		}
		
		op_pk_nfd_set(pkt, "D", destOnly); // request answer from destination directly, if TRUE
		
		/*	6.3
			An originating node often expects to have bidirectional
			communications with a destination node.  In such cases, it is not
			sufficient for the originating node to have a route to the
			destination node; the destination must also have a route back to the
			originating node.  In order for this to happen as efficiently as
			possible, any generation of a RREP by an intermediate node (as in
			section 6.6) for delivery to the originating node SHOULD be
			accompanied by some action that notifies the destination about a
			route back to the originating node.  The originating node selects
			this mode of operation in the intermediate nodes by setting the 'G'
			flag.  See section 6.6.3 for details about actions taken by the
			intermediate node in response to a RREQ with the 'G' flag set.
		*/
		
		op_pk_nfd_set(pkt, "G", gratuitous); 
		
		/*	6.3
			Before broadcasting the RREQ, the originating node buffers the RREQ
			ID and the Originator IP address (its own address) of the RREQ for
			PATH_DISCOVERY_TIME.  In this way, when the node receives the packet
			again from its neighbors, it will not reprocess and re-forward the
			packet.
		*/
		
		aodv_rreqs_create(aodv_myAddr, aodv_myInfo.reqId);
		op_pk_nfd_set(pkt, "STAT_ID", stats_nb_rreq);
	
	
		
		//REAL STATS
		stats_rreq [stats_nb_rreq].source 					= aodv_myAddr;
		stats_rreq [stats_nb_rreq].dest 					= destAddr;
		stats_rreq [stats_nb_rreq].rreq_nb_retry ++;
		if (stats_rreq [stats_nb_rreq].rrep_time_reception == 0)
			stats_rreq [stats_nb_rreq].rreq_time_emission 	= op_sim_time();
		stats_nb_rreq++;
		if (stats_nb_rreq >= MAX_RREQ_PK)
			op_sim_end("We have too many RREQ pk", "please increase MAX_RREQ_PK","","");
		
		
		aodv_pk_send_to_mac(pkt, nextHopAddr);
		
		dbg_print(1, "RREQ for node %d sent (TTL %i, retries %i)\n", destAddr, ttl, rte->rreqRetries);
	}

/** 
 * broadcast a route request RREQ 
 *
 * @parm destAddr		Address for which a route is requested
 * @parm ttl			Time to live (for expanding ring search)
 */
void aodv_pk_send_rreq(AodvT_Address destAddr, int ttl) 
	{		
		aodv_pk_send_rreq_to_addr(destAddr, ttl, AODV_BROADCAST_ADDR);
	}


/**
 * send a RREP
 * 
 * @parm destAddr
 * @parm destSeqNo
 * @parm originAddr
 * @parm lifetime
 */
void aodv_pk_send_rrep(	
		AodvT_Address 	destAddr,
		AodvT_SeqNo		destSeqNo,
		AodvT_Address	originAddr,
		AodvT_Time		lifetime,
		int				stat_id
	)
	{
		Packet* pkt_rrep;
		AodvT_rte* rte;
		
		pkt_rrep = op_pk_create_fmt("aodv_rrep");
		
		op_pk_nfd_set(pkt_rrep, "Dest_IPAddr", 		destAddr);
		op_pk_nfd_set(pkt_rrep, "Dest_SeqNo", 		destSeqNo);
		op_pk_nfd_set(pkt_rrep, "Origin_IPAddr", 	originAddr);
		op_pk_nfd_set(pkt_rrep, "Lifetime", 		lifetime);
		
		op_pk_nfd_set(pkt_rrep, "PrevHop", 			aodv_myAddr);
		op_pk_nfd_set(pkt_rrep, "STAT_ID", 			stat_id);
						
		rte = aodv_rte_get(originAddr);
		assert(NULL != rte);
		assert(rte->routeValid);
		
		
		//REAL STATS
		if (stats_rreq[stat_id].rrep_time_emission == 0)
			stats_rreq[stat_id].rrep_time_emission = op_sim_time();
		stats_rreq[stat_id].rrep_hops			= 0;
		stats_rreq[stat_id].rrep_nb_retry 		= 1;
		
		
		aodv_pk_send_to_mac_delayed(pkt_rrep, rte->nextHopAddr , op_dist_uniform(0.05));
		
		dbg_print(1, "Sent RREP for node %d to origin %d via %d by me as intermediate node\n", 
			destAddr, originAddr, rte->nextHopAddr);
	}

/**
 * send a RREP from an intermediate node
 * 
 * @parm destAddr
 * @parm destSeqNo
 * @parm originAddr
 * @parm lifetime
 * @parm hopCount
 */
void aodv_pk_send_rrep_intermediate(	
		AodvT_Address 	destAddr,
		AodvT_SeqNo		destSeqNo,
		AodvT_Address	originAddr,
		AodvT_Time		lifetime,
		int				hopCount,
		int				stat_id
	)
	{
		Packet* pkt_rrep;
		AodvT_rte* rte;
		
						
		pkt_rrep = op_pk_create_fmt("aodv_rrep");
		
		op_pk_nfd_set(pkt_rrep, "Dest_IPAddr", 		destAddr);
		op_pk_nfd_set(pkt_rrep, "Dest_SeqNo", 		destSeqNo);
		op_pk_nfd_set(pkt_rrep, "Origin_IPAddr", 	originAddr);
		op_pk_nfd_set(pkt_rrep, "Lifetime", 		lifetime);
		op_pk_nfd_set(pkt_rrep, "HopCount", 		hopCount);
		
		op_pk_nfd_set(pkt_rrep, "PrevHop", 			aodv_myAddr);
						
		rte = aodv_rte_get(originAddr);
		assert(NULL != rte);
		assert(rte->routeValid);
		
		
		//REAL STATS
		if (stats_rreq[stat_id].rrep_time_emission == 0)
			stats_rreq[stat_id].rrep_time_emission = op_sim_time();
		stats_rreq[stat_id].rrep_hops			= 0;
		stats_rreq[stat_id].rrep_nb_retry 		= 1;

		
		aodv_pk_send_to_mac(pkt_rrep, rte->nextHopAddr);
		
		dbg_print(1, "Sent RREP for node %d to origin %d via %d by me as intermediate node\n", 
			destAddr, originAddr, rte->nextHopAddr);
	}

/**
 * send a gratuitous RREP
 * 
 * @parm destAddr
 * @parm destSeqNo
 * @parm originAddr
 * @parm lifetime
 * @parm hopCount
 */
void aodv_pk_send_rrep_gratuitous(	
		AodvT_Address 	destAddr,
		AodvT_SeqNo		destSeqNo,
		AodvT_Address	originAddr,
		AodvT_Time		lifetime,
		int				hopCount,
		int				stat_id
	)
	{
		Packet* pkt_rrep;
		AodvT_rte* rte;
						
		pkt_rrep = op_pk_create_fmt("aodv_rrep");
		op_pk_nfd_set(pkt_rrep, "Dest_IPAddr", 		destAddr);
		op_pk_nfd_set(pkt_rrep, "Dest_SeqNo", 		destSeqNo);
		op_pk_nfd_set(pkt_rrep, "Origin_IPAddr", 	originAddr);
		op_pk_nfd_set(pkt_rrep, "Lifetime", 		lifetime);
		op_pk_nfd_set(pkt_rrep, "HopCount", 		hopCount);
		
		op_pk_nfd_set(pkt_rrep, "PrevHop", 			aodv_myAddr);
						
		rte = aodv_rte_get(originAddr);
		assert(NULL != rte);
		assert(rte->routeValid);
				
		
		//REAL STATS
		if (stats_rreq[stat_id].rrep_time_emission == 0)
			stats_rreq[stat_id].rrep_time_emission = op_sim_time();
		stats_rreq[stat_id].rrep_hops			= 0;
		stats_rreq[stat_id].rrep_nb_retry 		= 1;

		

		aodv_pk_send_to_mac_delayed(pkt_rrep, rte->nextHopAddr, op_dist_uniform(0.05));
		
		dbg_print(1, "Sent gratuitous RREP for node %d to origin %d via %d by me as intermediate node\n", 
			destAddr, originAddr, rte->nextHopAddr);
	}

void aodv_pk_send_hello()
	{
		Packet* pkt_rrep;
		
		/*	6.9. Hello Messages

			A node MAY offer connectivity information by broadcasting local Hello
			messages.  A node SHOULD only use hello messages if it is part of an
			active route.  Every HELLO_INTERVAL milliseconds, the node checks
			whether it has sent a broadcast (e.g., a RREQ or an appropriate layer
			2 message) within the last HELLO_INTERVAL.  If it has not, it MAY
			broadcast a RREP with TTL = 1, called a Hello message, with the RREP
			message fields set as follows:

			  Destination IP Address         The node's IP address.

			  Destination Sequence Number    The node's latest sequence number.

			  Hop Count                      0
			
			  Lifetime                       ALLOWED_HELLO_LOSS * HELLO_INTERVAL

			A node MAY determine connectivity by listening for packets from its
			set of neighbors.  If, within the past DELETE_PERIOD, it has received
			a Hello message from a neighbor, and then for that neighbor does not
			receive any packets (Hello messages or otherwise) for more than
			ALLOWED_HELLO_LOSS * HELLO_INTERVAL milliseconds, the node SHOULD
			assume that the link to this neighbor is currently lost.  When this
			happens, the node SHOULD proceed as in Section 6.11.

			Whenever a node receives a Hello message from a neighbor, the node
			SHOULD make sure that it has an active route to the neighbor, and
			create one if necessary.  If a route already exists, then the
			Lifetime for the route should be increased, if necessary, to be at
			least ALLOWED_HELLO_LOSS * HELLO_INTERVAL.  The route to the
			neighbor, if it exists, MUST subsequently contain the latest
			Destination Sequence Number from the Hello message.  The current node
			can now begin using this route to forward data packets.  Routes that
			are created by hello messages and not used by any other active routes
			will have empty precursor lists and would not trigger a RERR message
			if the neighbor moves away and a neighbor timeout occurs.
	   */
						
		pkt_rrep = op_pk_create_fmt("aodv_rrep");
		
		op_pk_nfd_set(pkt_rrep, "Dest_IPAddr", 		aodv_myAddr);
		op_pk_nfd_set(pkt_rrep, "Dest_SeqNo", 		aodv_myInfo.seqNo);
		op_pk_nfd_set(pkt_rrep, "Origin_IPAddr", 	AODV_BROADCAST_ADDR);
		op_pk_nfd_set(pkt_rrep, "Lifetime", 		AODV_ALLOWED_HELLO_LOSS * AODV_HELLO_INTERVAL);
		
		op_pk_nfd_set(pkt_rrep, "PrevHop", 			aodv_myAddr);
		op_pk_nfd_set(pkt_rrep, "TTL", 				1);
		

		aodv_pk_send_to_mac(pkt_rrep, AODV_BROADCAST_ADDR);
		
		dbg_print(1, "Sent RREP (HELLo) for node %d\n", aodv_myAddr);
	}

/**
 * send a RERR
 * 
 * @parm destAddr	Erroneous node
 */
void aodv_pk_send_rerr(AodvT_Address destAddr)
	{
		AodvT_rte* rte;
//		AodvT_rte* rte2;
		int errAddrCount;
		int pktSize;
		AodvT_Address* addrListPtr;
		AodvT_Address* addrPtr;
		Packet* unreachableDestsPk;
		Packet* pk_rerr;
		int i;
		
		AodvT_Address rerrDest = AODV_BROADCAST_ADDR;
		int precursorCount = 0;
	
		rte = aodv_rte_get(destAddr);
		assert(rte == NULL || !rte->routeValid); // NO valid route
						
		// generate RERR (route does not exist or is invalid)
					
		errAddrCount = 1; // destAddr
						

		/*	6.11
			A node initiates processing for a RERR message in three situations:
		
		    (i)       if it detects a link break for the next hop of an active
					  route in its routing table while transmitting data (and
					  route repair, if attempted, was unsuccessful), or

			(ii)      if it gets a data packet destined to a node for which it
					  does not have an active route and is not repairing (if
					  using local repair), or
		
		*/
						
		pktSize = errAddrCount * (sizeof(AodvT_Address) + sizeof(AodvT_SeqNo)); // in bytes
					
		addrListPtr = op_prg_mem_alloc(pktSize);
		addrPtr = addrListPtr;
		*(addrPtr++) = destAddr;
		if (rte != NULL)
			{
				/*	6.11
					Just before transmitting the RERR, certain updates are made on the
					routing table that may affect the destination sequence numbers for
					the unreachable destinations.  For each one of these destinations,
					the corresponding routing table entry is updated as follows:

					1. The destination sequence number of this routing entry, if it
					   exists and is valid, is incremented for cases (i) and (ii) above,
					   and copied from the incoming RERR in case (iii) above.

					2. The entry is invalidated by marking the route entry as invalid

					3. The Lifetime field is updated to current time plus DELETE_PERIOD.
					   Before this time, the entry SHOULD NOT be deleted.
				*/
				
				if (rte->destSeqNoValid)
					*(addrPtr++) = ++rte->destSeqNo; // update destSeqNo
				else
					*(addrPtr++) = 0; // unknown seqNo
				
				aodv_rte_invalidate_route(rte);
				
				if (op_prg_list_size(rte->precursors) > 0)
					{
						precursorCount += op_prg_list_size(rte->precursors);
						if (precursorCount == 1)
							{
								AodvT_rte* tmpRte;
								
								rerrDest = *((int*) op_prg_list_access(rte->precursors, OPC_LISTPOS_HEAD));
								tmpRte = aodv_rte_get(rerrDest);
								if (tmpRte == NULL || !tmpRte->routeValid)
									{
										// we do no longer have a route to this precursor, ignore it
										rerrDest = AODV_BROADCAST_ADDR;
										precursorCount = 0;
									}
							}
					}
			}
		else
			{
				*(addrPtr++) = 0; // unknown seqNo
			}
					
/* NOT IN RFC (see above)
		if (2 == errAddrCount)
			{
				*(addrPtr++) = rte->nextHopAddr;
				if (rte2 != NULL && rte2->destSeqNoValid)
					{
						*(addrPtr++) = ++rte2->destSeqNo; // update destSeqNo
					}
				else
					{
						*(addrPtr++) = 0;
					}
			}
*/
		
		if (precursorCount > 0)
			{
				// debug
				addrPtr = addrListPtr;
				for (i = 0; i < errAddrCount; i++)
					{
						dbg_print(1, "RERR info for node %i (seqNo %i) to be sent\n", *(addrPtr++), *(addrPtr++));
					}
					
				unreachableDestsPk = op_pk_create(pktSize*8);
				op_pk_fd_set(unreachableDestsPk, 0, OPC_FIELD_TYPE_STRUCT, addrListPtr, pktSize*8,
					op_prg_mem_copy_create, op_prg_mem_free, pktSize);
		
				pk_rerr = op_pk_create_fmt("aodv_rerr");
				op_pk_nfd_set(pk_rerr, "DestCount", errAddrCount);
				op_pk_nfd_set(pk_rerr, "UnreachableDestinations", unreachableDestsPk);
				op_pk_nfd_set(pk_rerr, "PrevHop", aodv_myAddr);
		
		
				/*	6.11 
					A Route Error (RERR) message MAY be either broadcast (if there are
					many precursors), unicast (if there is only 1 precursor), or
					iteratively unicast to all precursors (if broadcast is
					inappropriate).
				*/
		
				if (precursorCount == 1)
					{
						aodv_pk_send_to_mac(pk_rerr, rerrDest);
						dbg_print(1, "Unicasting RERR to node %i for destination %i\n", rerrDest, destAddr);
					}
				else
					{
						aodv_pk_send_to_mac(pk_rerr, AODV_BROADCAST_ADDR);
						dbg_print(1, "Broadcasting RERR for destination %i\n", destAddr);
					}
			}
		else
			{
				dbg_print(100, "RERR info for node %i (seqNo %i) NOT sent: no active precursors\n", *(addrPtr++), *(addrPtr++));
				op_prg_mem_free(addrListPtr);
			}
	}


/* *** Packet handling functions *************************************************************************** */

/*
   6.2. Route Table Entries and Precursor Lists

   When a node receives an AODV control packet from a neighbor, or
   creates or updates a route for a particular destination or subnet, it
   checks its route table for an entry for the destination.  In the
   event that there is no corresponding entry for that destination, an
   entry is created.  The sequence number is either determined from the
   information contained in the control packet, or else the valid
   sequence number field is set to false.  The route is only updated if
   the new sequence number is either

   (i)       higher than the destination sequence number in the route
             table, or

   (ii)      the sequence numbers are equal, but the hop count (of the
             new information) plus one, is smaller than the existing hop
             count in the routing table, or

   (iii)     the sequence number is unknown.

   The Lifetime field of the routing table entry is either determined
   from the control packet, or it is initialized to
   ACTIVE_ROUTE_TIMEOUT.  This route may now be used to send any queued
   data packets and fulfills any outstanding route requests.

   Each time a route is used to forward a data packet, its Active Route
   Lifetime field of the source, destination and the next hop on the
   path to the destination is updated to be no less than the current
   time plus ACTIVE_ROUTE_TIMEOUT.  Since the route between each
   originator and destination pair is expected to be symmetric, the
   Active Route Lifetime for the previous hop, along the reverse path
   back to the IP source, is also updated to be no less than the current
   time plus ACTIVE_ROUTE_TIMEOUT.  The lifetime for an Active Route is
   updated each time the route is used regardless of whether the
   destination is a single node or a subnet.

   For each valid route maintained by a node as a routing table entry,
   the node also maintains a list of precursors that may be forwarding
   packets on this route.  These precursors will receive notifications
   from the node in the event of detection of the loss of the next hop
   link.  The list of precursors in a routing table entry contains those
   neighboring nodes to which a route reply was generated or forwarded.
*/

/**
 * process a RREQ packet
 */
void aodv_handle_pk_rreq(Packet* pkt)
	{
		int				seqNoUnknown;
		int				gratuitous;
		int 			destOnly;
		int				hopCount;
		int				rreqId;
		AodvT_Address	destAddr;
		AodvT_SeqNo		destSeqNo;
		AodvT_Address	originAddr;
		AodvT_SeqNo		originSeqNo;
		
		AodvT_Address	prevHop;
		int				ttl;
		
		AodvT_rte* 		rte_o = NULL;	// origin
		AodvT_rte* 		rte_d = NULL;	// dest
		AodvT_rte* 		rte_p = NULL;	// prev
		AodvT_rte* 		rte_n = NULL;	// next
		AodvT_rreqte* 	rreq = NULL;
		
		int						stat_id;
		
		double lifetimePrevHop = 0;
		double lifetimeOriginAddr = 0;
		
		op_pk_nfd_get(pkt, "U", 			&seqNoUnknown);
		op_pk_nfd_get(pkt, "G", 			&gratuitous);
		op_pk_nfd_get(pkt, "D", 			&destOnly);
		op_pk_nfd_get(pkt, "HopCount", 		&hopCount);
		op_pk_nfd_get(pkt, "RREQ_ID", 		&rreqId);
		op_pk_nfd_get(pkt, "Dest_IPAddr", 	&destAddr);
		op_pk_nfd_get(pkt, "Dest_SeqNo", 	&destSeqNo);
		op_pk_nfd_get(pkt, "Origin_IPAddr", &originAddr);
		op_pk_nfd_get(pkt, "Origin_SeqNo", 	&originSeqNo);
		
/*		
		// get previous hop from mac layer
		ici_ptr = op_intrpt_ici();
		assert(NULL != ici_ptr);
		op_ici_attr_get(ici_ptr, "src_addr", &prevHop);
*/
		
		// get previous hop & TTL
		op_pk_nfd_get(pkt, "PrevHop", 		&prevHop);
		op_pk_nfd_get(pkt, "TTL", 			&ttl);
		

		
		// stats
		op_pk_nfd_get(pkt, "STAT_ID",		&stat_id);		
		
		
		// debug
		dbg_print(1, "RREQ: dest %d, origin %d, prevHop %d, reqId %d\n", destAddr, originAddr, prevHop, rreqId);
		
		
		/*	6.5
			When a node receives a RREQ, it first creates or updates a route to
			the previous hop without a valid sequence number (see section 6.2)
		*/
		rte_p = aodv_rte_get(prevHop);
		if (NULL == rte_p) 
			{
				rte_p = aodv_rte_create(prevHop);
			}
		//if (!rte_p->destSeqNoValid || !rte_p->routeValid) // TODO: verify with comment above
		if (1) // TODO: verify with comment above
			{
				rte_p->nextHopAddr = prevHop; // the node itself
				rte_p->hopCount = 1;
				
				dbg_print(1, "Route update: node %i now reach over node %i\n", rte_p->destAddr, rte_p->nextHopAddr);
			}
		aodv_rte_activate_route(rte_p);
		lifetimePrevHop = rte_p->lifetime;
		
		
		/*	6.5
			then checks to determine whether it has received a RREQ with the same
			Originator IP Address and RREQ ID within at least the last
			PATH_DISCOVERY_TIME.  If such a RREQ has been received, the node
			silently discards the newly received RREQ.
		*/
		rreq = aodv_rreqs_get(originAddr, rreqId);
		if (NULL != rreq)
			{
				// discard packet
				op_pk_destroy(pkt);
				//dbg_print(1, "Already received RREQ packet, discarding\n");
				return;
			}
		aodv_rreqs_create(originAddr, rreqId);
		
		/*	6.5
			First, it first increments the hop count value in the RREQ by one, to
			account for the new hop through the intermediate node.  Then the node
			searches for a reverse route to the Originator IP Address (see
			section 6.2), using longest-prefix matching.  If need be, the route
			is created, or updated using the Originator Sequence Number from the
			RREQ in its routing table.  This reverse route will be needed if the
			node receives a RREP back to the node that originated the RREQ
			(identified by the Originator IP Address). 
		*/
		
		// increment hop count and decrement TTL
		hopCount++;
		
		// update/create route to the originator of the RREQ
		rte_o = aodv_rte_get(originAddr);
		if (NULL == rte_o) 
			{
				rte_o = aodv_rte_create(originAddr);
			}
		if (rte_o->routeValid)
			{
				lifetimeOriginAddr = rte_o->lifetime;
			}	
		else
			{
				lifetimeOriginAddr = 0;
			}
		
		if ((!rte_o->routeValid || !rte_o->destSeqNoValid || (rte_o->destSeqNo < originSeqNo) || 
			((rte_o->destSeqNo == originSeqNo) && (rte_o->hopCount+1 > hopCount))) &&
			(rte_p->nextHopAddr == rte_p->destAddr)) // only, if the prevHop is a direct neighbor
			{
				aodv_rte_activate_route(rte_o);
			
				/*	6.5
					When the reverse route is
					created or updated, the following actions on the route are also
					carried out:

					1. the Originator Sequence Number from the RREQ is compared to the
					   corresponding destination sequence number in the route table entry
					   and copied if greater than the existing value there

					2. the valid sequence number field is set to true;

					3. the next hop in the routing table becomes the node from which the
					   RREQ was received (it is obtained from the source IP address in
					   the IP header and is often not equal to the Originator IP Address
					   field in the RREQ message);
				
					4. the hop count is copied from the Hop Count in the RREQ message;
				*/
				
				if (!rte_o->destSeqNoValid || (originSeqNo > rte_o->destSeqNo))
					{
						rte_o->destSeqNo = originSeqNo;
						rte_o->destSeqNoValid = TRUE;
					}
				
				rte_o->nextHopAddr = prevHop; 
				rte_o->hopCount = hopCount;
				
				dbg_print(1, "Route update: node %i now reach over node %i\n", rte_o->destAddr, rte_o->nextHopAddr);
			}
		
		if (!rte_o->routeValid)
			{
				aodv_rte_dbg_print(100);
				dbg_print(100, "origin: %i\n", rte_o->destAddr);
				assert(0);
			}
		
		/*	6.5
			Whenever a RREQ message is received, the Lifetime of the reverse
			route entry for the Originator IP address is set to be the maximum of
			(ExistingLifetime, MinimalLifetime), where

			MinimalLifetime =    (current time + 2*NET_TRAVERSAL_TIME -
								  2*HopCount*NODE_TRAVERSAL_TIME).
		*/
		aodv_rte_update_lifetime(rte_p, 
			max(lifetimePrevHop, 
				op_sim_time() + 2*AODV_NET_TRAVERSAL_TIME - 2*hopCount*AODV_NODE_TRAVERSAL_TIME));
		aodv_rte_update_lifetime(rte_o, 
			max(lifetimeOriginAddr, 
				op_sim_time() + 2*AODV_NET_TRAVERSAL_TIME - 2*hopCount*AODV_NODE_TRAVERSAL_TIME));

		
		/*	6.5
			if a node does generate a RREP, then the node discards the
			RREQ.  Notice that, if intermediate nodes reply to every transmission
			of RREQs for a particular destination, it might turn out that the
			destination does not receive any of the discovery messages.  In this
			situation, the destination does not learn of a route to the
			originating node from the RREQ messages.  This could cause the
			destination to initiate a route discovery (for example, if the
			originator is attempting to establish a TCP session).  In order that
			the destination learn of routes to the originating node, the
			originating node SHOULD set the "gratuitous RREP" ('G') flag in the
			RREQ if for any reason the destination is likely to need a route to
			the originating node.  If, in response to a RREQ with the 'G' flag
			set, an intermediate node returns a RREP, it MUST also unicast a
			gratuitous RREP to the destination node (see section 6.6.3).
		*/
		
		if (destAddr == aodv_myAddr)
			{
				// we are the node for which the route was requested
				dbg_print(1, "RREQ for us!\n");
				
				/*
					6.6.1. Route Reply Generation by the Destination

					If the generating node is the destination itself, it MUST increment
					its own sequence number by one if the sequence number in the RREQ
					packet is equal to that incremented value.  Otherwise, the
					destination does not change its sequence number before generating the
					RREP message.  The destination node places its (perhaps newly
					incremented) sequence number into the Destination Sequence Number
					field of the RREP, and enters the value zero in the Hop Count field
					of the RREP.

					The destination node copies the value MY_ROUTE_TIMEOUT (see section
					10) into the Lifetime field of the RREP.  Each node MAY reconfigure
					its value for MY_ROUTE_TIMEOUT, within mild constraints (see section
					10).
				*/
				
				// the received destSeqNo may be greater than our own
				// because of several RERR...
				if (!seqNoUnknown && destSeqNo > aodv_myInfo.seqNo)
					aodv_myInfo.seqNo = destSeqNo;
								
				// send RREP
				aodv_pk_send_rrep(
					destAddr, 						// Dest_IPAddr
					aodv_myInfo.seqNo, 				// Dest_SeqNo
					originAddr, 					// Origin_IPAddr
					(double) AODV_MY_ROUTE_TIMEOUT,	// Lifetime
					stat_id							// RREQ id
				);
				
				
				/*// stats
				stats_rreq_->time_reception = op_sim_time();
				stats_rreq_->nb_rreps++;
				stats_rreq_->hops = hopCount;
				*/
				
				//REAL STATS
				stats_rreq[stat_id].rreq_time_reception	= op_sim_time();
				stats_rreq[stat_id].nb_rreps++;
				stats_rreq[stat_id].rreq_hops			= hopCount;
				
				
				aodv_rte_dbg_print(1);
				
				op_pk_destroy(pkt);
			}
		else
			{
				rte_d = aodv_rte_get(destAddr);
				if (NULL == rte_d) 
					{
						rte_d = aodv_rte_create(destAddr);
					}
				
				// if the next hop is the origin node of the RREQ, the origin has no longer a 
				// route to the destination, so our entry is invalid, too!
				if (rte_o->destAddr == rte_d->nextHopAddr && rte_d->routeValid)
					aodv_rte_invalidate_route(rte_d);
				
				// dito for previous hop
				if (rte_p->destAddr == rte_d->nextHopAddr && rte_d->routeValid)
					aodv_rte_invalidate_route(rte_d);
				
				if (rte_d->routeValid &&
					rte_d->destSeqNoValid && 
					rte_d->destSeqNo >= destSeqNo &&
					!destOnly)
					{						
						// reply by an intermediate node with a RREP
						dbg_print(1, "RREQ for a known node!\n");
						
						/*
							6.6.2. Route Reply Generation by an Intermediate Node

							If the node generating the RREP is not the destination node, but
							instead is an intermediate hop along the path from the originator to
							the destination, it copies its known sequence number for the
							destination into the Destination Sequence Number field in the RREP
							message.

							The intermediate node updates the forward route entry by placing the
							last hop node (from which it received the RREQ, as indicated by the
							source IP address field in the IP header) into the precursor list for
							the forward route entry -- i.e., the entry for the Destination IP
							Address.  The intermediate node also updates its route table entry
							for the node originating the RREQ by placing the next hop towards the
							destination in the precursor list for the reverse route entry --
							i.e., the entry for the Originator IP Address field of the RREQ
							message data.

							The intermediate node places its distance in hops from the
							destination (indicated by the hop count in the routing table) Count
							field in the RREP.  The Lifetime field of the RREP is calculated by
							subtracting the current time from the expiration time in its route
							table entry.
	   					*/
						
						assert((rte_d->lifetime - op_sim_time()) > 0);
						
						rte_n = aodv_rte_get(rte_d->nextHopAddr);
						assert(rte_n != NULL);
						
						aodv_rte_precursors_add(rte_d, rte_o->nextHopAddr);
						aodv_rte_precursors_add(rte_n, rte_o->nextHopAddr);
						aodv_rte_precursors_add(rte_o, rte_d->nextHopAddr);
						aodv_rte_precursors_add(rte_p, rte_d->nextHopAddr);
						
						aodv_pk_send_rrep_intermediate(
								destAddr, 							// Dest_IPAddr
								rte_d->destSeqNo, 					// Dest_SeqNo
								originAddr, 						// Origin_IPAddr
								rte_d->lifetime - op_sim_time(),	// Lifetime
								rte_d->hopCount,					// HopCount of route to destAddr
								stat_id								// RREQ_id
							);
						
												
						// stats
						/*stats_rreq_->time_reception = op_sim_time();
						stats_rreq_->nb_rreps_intermediate++;
						stats_rreq_->hops = hopCount;
						*/
						
						//REAL STATS
						stats_rreq[stat_id].rreq_time_reception	= op_sim_time();
						stats_rreq[stat_id].nb_rreps++;
						stats_rreq[stat_id].rreq_hops			= hopCount;
					
						if (gratuitous)
							{
								/*
									6.6.3. Generating Gratuitous RREPs

									After a node receives a RREQ and responds with a RREP, it discards
									the RREQ.  If the RREQ has the 'G' flag set, and the intermediate
									node returns a RREP to the originating node, it MUST also unicast a
									gratuitous RREP to the destination node.  The gratuitous RREP that is
									to be sent to the desired destination contains the following values
									in the RREP message fields:

									Hop Count                        The Hop Count as indicated in the
																	 node's route table entry for the
																	 originator

									Destination IP Address           The IP address of the node that
																	 originated the RREQ

									Destination Sequence Number      The Originator Sequence Number from
																	 the RREQ

									Originator IP Address            The IP address of the Destination
																	 node in the RREQ

									Lifetime                         The remaining lifetime of the route
																	 towards the originator of the RREQ,
																	 as known by the intermediate node.

									The gratuitous RREP is then sent to the next hop along the path to
									the destination node, just as if the destination node had already
									issued a RREQ for the originating node and this RREP was produced in
									response to that (fictitious) RREQ.  The RREP that is sent to the
									originator of the RREQ is the same whether or not the 'G' bit is set.
								*/
							
								// send gratuitous RREP to destination node
								assert(rte_o != NULL && rte_o->routeValid);
								assert((rte_o->lifetime - op_sim_time()) > 0);
								
								aodv_pk_send_rrep_gratuitous(
									originAddr,									// Dest_IPAddr
									originSeqNo, 								// Dest_SeqNo
									destAddr, 									// Origin_IPAddr
									(double) (rte_o->lifetime - op_sim_time()),	// Lifetime of route to originAddr
									rte_o->hopCount,								// HopCount of route to originAddr
									stat_id										// RREQ id
								);
							}
				
						op_pk_destroy(pkt);
					}
				else
					{
						/*	6.5
							If a node does not generate a RREP (following the processing rules in
							section 6.6), and if the incoming IP header has TTL larger than 1,
							the node updates and broadcasts the RREQ to address 255.255.255.255
							on each of its configured interfaces (see section 6.14).  To update
							the RREQ, the TTL or hop limit field in the outgoing IP header is
							decreased by one, and the Hop Count field in the RREQ message is
							incremented by one, to account for the new hop through the
							intermediate node.  Lastly, the Destination Sequence number for the
							requested destination is set to the maximum of the corresponding
							value received in the RREQ message, and the destination sequence
							value currently maintained by the node for the requested destination.
							However, the forwarding node MUST NOT modify its maintained value for
							the destination sequence number, even if the value received in the
							incoming RREQ is larger than the value currently maintained by the
							forwarding node.
						*/

						if (ttl > 1) 
							{
								// decrement TTL
								ttl--; 
								
								// hopCount already incremented
								
								assert(rte_d != NULL);
							
								// update the destination's sequence number for the packet if we have a newer one
								if (rte_d->destSeqNoValid && (seqNoUnknown || rte_d->destSeqNo > destSeqNo))
									{
										destSeqNo = rte_d->destSeqNo;
										seqNoUnknown = 0;
									}
							
								op_pk_nfd_set(pkt, "U", 			seqNoUnknown);
								op_pk_nfd_set(pkt, "HopCount", 		hopCount);
								op_pk_nfd_set(pkt, "Dest_SeqNo", 	destSeqNo);
				
								op_pk_nfd_set(pkt, "PrevHop", 		aodv_myAddr);
								op_pk_nfd_set(pkt, "TTL", 			ttl);
		
								aodv_pk_send_to_mac_delayed(pkt, AODV_BROADCAST_ADDR , op_dist_uniform(0.05));
		
								dbg_print(1, "RREQ from node %d for node %d (received over node %d) relayed\n", 
									originAddr, destAddr, prevHop);
								
							}
						else
							{
								dbg_print(1, "RREQ not relayed (TTL exceeded)\n");
								
								op_pk_destroy(pkt);
							}
					}
				
				aodv_rte_dbg_print(1);
			}

		
	}

/**
 * process a RREP packet (6.7)
 */
void aodv_handle_pk_rrep(Packet* pkt)
	{
		int 			repair;
		int 			acknowledge;
		int 			prefixSize;
		int				hopCount, newHopCount;
		AodvT_Address	destAddr;
		AodvT_SeqNo		destSeqNo;
		AodvT_Address	originAddr;
		double			lifetime;
		int				stat_id;
		
		AodvT_Address	prevHop;
		int				ttl;
		
		char			msg[1000];
		
		AodvT_rte* 		rte_p = NULL;	// prev
		AodvT_rte* 		rte_d = NULL;	// dest
		AodvT_rte* 		rte_o = NULL;	// origin
		AodvT_rte* 		rte_n = NULL;	// next
		
		BOOL			destUpdated = FALSE;
		
		op_pk_nfd_get(pkt, "R", 			&repair);
		op_pk_nfd_get(pkt, "A", 			&acknowledge);
		op_pk_nfd_get(pkt, "PrefixSize",	&prefixSize);
		op_pk_nfd_get(pkt, "HopCount", 		&hopCount);
		op_pk_nfd_get(pkt, "Dest_IPAddr", 	&destAddr);
		op_pk_nfd_get(pkt, "Dest_SeqNo", 	&destSeqNo);
		op_pk_nfd_get(pkt, "Origin_IPAddr", &originAddr);
		op_pk_nfd_get(pkt, "Lifetime", 		&lifetime);
		
		// get previous hop & TTL
		op_pk_nfd_get(pkt, "PrevHop", 		&prevHop);
		op_pk_nfd_get(pkt, "TTL", 			&ttl);
		
		op_pk_nfd_get(pkt, "STAT_ID", 		&stat_id);
		
		if (destAddr == aodv_myAddr)
			return;
		//	assert(0);

		assert(lifetime > 0);
		
		// TODO: not yet implemented
		assert(!repair);
		assert(!acknowledge);
		assert(0 == prefixSize);
		
		/*	6.7
			When a node receives a RREP message, it searches (using longest-
			prefix matching) for a route to the previous hop.  If needed, a route
			is created for the previous hop, but without a valid sequence number
			(see section 6.2).
		*/
		
		// check RT entry for previous hop
		rte_p = aodv_rte_get(prevHop);
		if (NULL == rte_p)
			{
				rte_p = aodv_rte_create(prevHop);
			}
		//if (!rte_p->destSeqNoValid || !rte_p->routeValid)
		if (!rte_p->routeValid)
			{	
				rte_p->nextHopAddr = prevHop;
				rte_p->hopCount = 1;
				
				dbg_print(1, "Route update: node %i now reach over node %i\n", rte_p->destAddr, rte_p->nextHopAddr);
			}
		aodv_rte_activate_route(rte_p);
		aodv_rte_update_lifetime(rte_p, op_sim_time() + lifetime);
		
		/*	6.7
			Next, the node then increments the hop count
			value in the RREP by one, to account for the new hop through the
			intermediate node.  Call this incremented value the "New Hop Count".
		*/
		newHopCount = hopCount + 1;
		
		/* 	6.7
			Then the forward route for this destination is created if it does not
			already exist.
		*/
		if (destAddr == prevHop)
			rte_d = rte_p;
		else				
			rte_d = aodv_rte_get(destAddr);
		if (NULL == rte_d)
			{
				rte_d = aodv_rte_create(destAddr);
			}
		
		/*	6.7
			Otherwise, the node compares the Destination Sequence
			Number in the message with its own stored destination sequence number
			for the Destination IP Address in the RREP message.  Upon comparison,
			the existing entry is updated only in the following circumstances:

			(i)       the sequence number in the routing table is marked as
					  invalid in route table entry.

			(ii)      the Destination Sequence Number in the RREP is greater than
					  the node's copy of the destination sequence number and the
					  known value is valid, or

			(iii)     the sequence numbers are the same, but the route is is
					  marked as inactive, or

			(iv)      the sequence numbers are the same, and the New Hop Count is
					  smaller than the hop count in route table entry.
		*/

		if (    (
					(!rte_d->destSeqNoValid )
							|| 
					(rte_d->destSeqNo < destSeqNo) 
							|| 
					((rte_d->destSeqNo == destSeqNo) && (!rte_d->routeValid || newHopCount < rte_d->hopCount))
				) 
			&&
			(rte_p->nextHopAddr == rte_p->destAddr))
			{	
				/*	6.7
					If the route table entry to the destination is created or updated,
					then the following actions occur:

					-  the route is marked as active,

					-  the destination sequence number is marked as valid,

					-  the next hop in the route entry is assigned to be the node from
					   which the RREP is received, which is indicated by the source IP
					   address field in the IP header,

					-  the hop count is set to the value of the New Hop Count,

					-  the expiry time is set to the current time plus the value of the
					   Lifetime in the RREP message,

					-  and the destination sequence number is the Destination Sequence
					   Number in the RREP message.
				*/
				aodv_rte_activate_route(rte_d);
				rte_d->destSeqNoValid = TRUE;
				rte_d->nextHopAddr = prevHop;
				rte_d->hopCount = newHopCount;
				rte_d->destSeqNo = destSeqNo;
				aodv_rte_update_lifetime(rte_d, op_sim_time() + lifetime);
				
				dbg_print(1, "Route update: node %i now reach over node %i\n", rte_d->destAddr, rte_d->nextHopAddr);
				
				destUpdated = TRUE;
			}
		
		if (originAddr == AODV_BROADCAST_ADDR)
			{
				// this was a hello packet
				op_pk_destroy(pkt);
				return;
			}
		

		
		if (originAddr != aodv_myAddr)
			{
				//I MUST forward the RREp even if I didn't update my routing cache (the destination of the RREp has perhaps not this routing entry !!!!!)
				if (1)//destUpdated)
					{
						// forward packet
			
						/*	6.7
							If the current node is not the node indicated by the Originator IP
							Address in the RREP message AND a forward route has been created or
							updated as described above, the node consults its route table entry
							for the originating node to determine the next hop for the RREP
							packet, and then forwards the RREP towards the originator using the
							information in that route table entry.  If a node forwards a RREP
							over a link that is likely to have errors or be unidirectional, the
							node SHOULD set the 'A' flag to require that the recipient of the
							RREP acknowledge receipt of the RREP by sending a RREP-ACK message
							back (see section 6.8).
				
							When any node transmits a RREP, the precursor list for the
							corresponding destination node is updated by adding to it the next
							hop node to which the RREP is forwarded.  Also, at each node the
							(reverse) route used to forward a RREP has its lifetime changed to be
							the maximum of (existing-lifetime, (current time +
							ACTIVE_ROUTE_TIMEOUT).  Finally, the precursor list for the next hop
							towards the destination is updated to contain the next hop towards
							the source.
				
							TODO: RREP_ACK
						*/
				
			
						rte_o = aodv_rte_get(originAddr);
						if (rte_o == NULL || !rte_o->routeValid)
							{	
								// this may happen when an intermediate node answered to a RREQ
								// and sent a gratuitous RREP via us while our entry expired
								// recently
								
								if (rte_o == NULL)
									{
										// this means that our entry expired a long time ago
										// which shouldn't happen
										dbg_print(100, "originAddr %i\n", originAddr);
										aodv_rte_dbg_print(100);
										assert(0);
									}
								
								// precursor list may be empty because we haven't had a valid
								// route till now!
								//assert(op_prg_list_size(rte_o->precursors) > 0);
								
								// send a RERR
								aodv_pk_send_rerr(rte_o->destAddr);
								
								op_pk_destroy(pkt);
							}
						else
							{
								rte_n = aodv_rte_get(rte_o->nextHopAddr);
								assert(rte_n != NULL); 
								if (!rte_n->routeValid)
									{
										aodv_rte_dbg_print(100);
										assert(0);
									}
				
								aodv_rte_update_lifetime(rte_o, max(rte_o->lifetime, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT));
								aodv_rte_update_lifetime(rte_n, max(rte_n->lifetime, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT));
						
								// precursors (add nextHop to origin to precursor lists of the destination and the next hop towards the destination)
								aodv_rte_precursors_add(rte_d, rte_n->destAddr);
								aodv_rte_precursors_add(rte_p, rte_n->destAddr);
								// add prevHop (next hop to destination) to precursor lists of the origin and and the next hop towards the origin
								aodv_rte_precursors_add(rte_o, rte_p->destAddr);
								aodv_rte_precursors_add(rte_n, rte_p->destAddr);
				
								op_pk_nfd_set(pkt, "HopCount", newHopCount);
								op_pk_nfd_set(pkt, "PrevHop",  aodv_myAddr);	
				
								aodv_pk_send_to_mac(pkt, rte_o->nextHopAddr);
				
								dbg_print(1, "RREP for dest %i forwarded (prevHop %i, nextHop %i)\n", 
									destAddr, prevHop, rte_o->nextHopAddr);
							}
					}
				else
					{
						if (0)//DEBUG)
							{
								sprintf(msg , "%d -- %d %d %d %d %d(%d %d) %d\n", aodv_myAddr , !rte_d->destSeqNoValid , (rte_d->destSeqNo < destSeqNo) , (rte_d->destSeqNo == destSeqNo) , !rte_d->routeValid , newHopCount < rte_d->hopCount , newHopCount , rte_d->hopCount , rte_p->nextHopAddr == rte_p->destAddr);
								debug_test(msg);
							}
						aodv_rte_dbg_print(1);
						dbg_print(1, "RREP NOT relayed (destination not updated, prevHop %i!\n", prevHop);
						
						op_pk_destroy(pkt);
					}
			}
		else
			{				
				dbg_print(1, "Got RREP from requested destination (prevHop %i, destAddr %i, destSeqNo %i)!\n", prevHop, destAddr, destSeqNo);
				
				
				// stats
				if ((stat_id != -1) && (stats_rreq	[stat_id].rrep_time_reception == 0))
					{
						stats_rreq	[stat_id].rrep_hops		 		= MAX_NETWORK_RADIUS - ttl;
						stats_rreq	[stat_id].rrep_time_reception 	= op_sim_time();
					}									
				
				
				
				
				// queued packets will be sent in the enter exec of the idle state!	
				
				/*
					Here, it is not sure that the the route to the destination is valid (rte_d->routeValid).
					It may happen, that we received just before a RERR with an higher seqNo, so the criteria
					in 6.7 to update the destination were not fulfilled.
				*/
				//assert(rte_d->routeValid)
				//assert(rte_p->acknowledged);
				
				if (!rte_d->routeValid && op_prg_list_size(rte_d->queuedPackets) > 0)
					{
						if (!rte_d->routeDiscovery)
							{
								aodv_rte_dbg_print(100);
								dbg_print(100, "dest %i\n", rte_d->destAddr);
								assert(0);
							}
					}
				
				op_pk_destroy(pkt);
			}
		
	}

/**
 * process a RERR packet (6.11)
 */
void aodv_handle_pk_rerr(Packet* pkt)
	{
		AodvT_Address prevHop;
		int noDelete;
		char destCount;
		Packet* unreachableDestsPk = NULL;
		
		AodvT_Address* addrListPtr = NULL;
		AodvT_Address* addrPtr = NULL;

		AodvT_Address addr;
		AodvT_SeqNo destSeqNo;
		
		AodvT_Address* myAddrListPtr = NULL;
		AodvT_Address* myAddrPtr = NULL;
		int myDestCount;
		
		int i;
		AodvT_rte* rte = NULL;
		
		AodvT_Address rerrDest = -1;	// destination where to forward the RERR (unicast)
		int precursorCount = 0;	// number of precursors concerned
		
		int pktSize;
		
		op_pk_nfd_get(pkt, "PrevHop", &prevHop);
		op_pk_nfd_get(pkt, "N", &noDelete);
		op_pk_nfd_get(pkt, "DestCount", &destCount);
		op_pk_nfd_get(pkt, "UnreachableDestinations", &unreachableDestsPk);
		assert(destCount > 0 && destCount < 256);
		assert(NULL != unreachableDestsPk);
		op_pk_fd_get(unreachableDestsPk, 0, &addrListPtr);
		assert(addrListPtr != NULL);
		dbg_print(1, "RERR info for node %i over node %i (seqNo %i), destCount %i\n", (*addrListPtr), prevHop, *(addrListPtr+1), destCount);
		assert(*addrListPtr != prevHop);
	
		// update transmitter of RERR
		rte = aodv_rte_get(prevHop);
		if (rte == NULL)
			{
				// unknown node, ignore RERR
				dbg_print(1, "Destroyed RERR\n");
				op_pk_destroy(pkt);
				op_pk_destroy(unreachableDestsPk);
				op_prg_mem_free(addrListPtr);
				
				return;
			}
		if (rte->nextHopAddr == prevHop)
			{
				// node known and the RERR comes over the known route => update life time
				aodv_rte_activate_route(rte);
			}
		
		// allocate memory for retransmitting only those addresses for which we are a precursor
		myAddrListPtr = op_prg_mem_alloc(destCount * (sizeof(AodvT_Address) + sizeof(AodvT_SeqNo)));
		assert(myAddrListPtr != NULL);
		myAddrPtr = myAddrListPtr;
		myDestCount = 0;
		
		addrPtr = addrListPtr;
		for (i = 0; i < destCount; i++)
			{
				addr = *addrPtr;
				destSeqNo = *(++addrPtr);
				
				rte = aodv_rte_get(addr);

				dbg_print(2, "RERR info for node %i over node %i (seqNo %i)\n", addr, prevHop, destSeqNo);
				assert(addr != prevHop);
				
				/*	6.11
					the list should consist of those destinations in the RERR
					for which there exists a corresponding entry in the local routing
					table that has the transmitter of the received RERR as the next hop.
				*/
				
				if (rte != NULL && rte->routeValid && rte->nextHopAddr == prevHop)
					{
						//dbg_print(1, "Invalidating destination %i\n", rte->destAddr);
					
						/*	6.11
							Just before transmitting the RERR, certain updates are made on the
							routing table that may affect the destination sequence numbers for
							the unreachable destinations.  For each one of these destinations,
							the corresponding routing table entry is updated as follows:

							1. [...] copied from the incoming RERR in case (iii) above.

							2. The entry is invalidated by marking the route entry as invalid

							3. The Lifetime field is updated to current time plus DELETE_PERIOD.
							   Before this time, the entry SHOULD NOT be deleted.
						*/
					
						aodv_rte_invalidate_route(rte);
						rte->destSeqNo = destSeqNo;
						
						/*	6.11
							The RERR should contain those destinations that are part of
							the created list of unreachable destinations and have a non-empty
							precursor list.
						*/
						
						if (op_prg_list_size(rte->precursors) > 0)
							{
								*(myAddrPtr++) = rte->destAddr;
								*(myAddrPtr++) = destSeqNo;
								myDestCount++;
								
								precursorCount += op_prg_list_size(rte->precursors);
								if (precursorCount == 1)
									{
										AodvT_rte* tmpRte;
									
										rerrDest = *((int*) op_prg_list_access(rte->precursors, OPC_LISTPOS_HEAD));
										tmpRte = aodv_rte_get(rerrDest);
										if (tmpRte == NULL || !tmpRte->routeValid)
											{
												// we do no longer have a route that node, ignore it
												rerrDest = AODV_BROADCAST_ADDR;
												precursorCount = 0;
												myDestCount--;
												
												myAddrPtr--; // revert destSeqNo
												myAddrPtr--; // revert destAddr
											}
									}
							}
						
						// if we have still have data queued, re-request a route
						if (op_prg_list_size(rte->queuedPackets) > 0)
							{
								if (!rte->routeDiscovery)
									aodv_initiate_rreq(rte, rte->hopCount + AODV_TTL_INCREMENT);
							}
					}
				addrPtr++;
			}
		
		if (myDestCount > 0 && precursorCount > 0)
			{	
				/*	6.11
					The neighboring node(s) that should receive the RERR are all those
					that belong to a precursor list of at least one of the unreachable
					destination(s) in the newly created RERR.  In case there is only one
					unique neighbor that needs to receive the RERR, the RERR SHOULD be
					unicast toward that neighbor.  Otherwise the RERR is typically sent
					to the local broadcast address (Destination IP == 255.255.255.255,
					TTL == 1) with the unreachable destinations, and their corresponding
					destination sequence numbers, included in the packet.  The DestCount
					field of the RERR packet indicates the number of unreachable
					destinations included in the packet.
	   			*/
			
				assert(precursorCount > 0);
			
				pktSize = myDestCount * (sizeof(AodvT_Address) + sizeof(AodvT_SeqNo)); // in bytes
				
				op_pk_destroy(unreachableDestsPk);
				unreachableDestsPk = op_pk_create(pktSize*8);
				
				op_pk_fd_set(unreachableDestsPk, 0, OPC_FIELD_TYPE_STRUCT, myAddrListPtr, 
					pktSize*8, op_prg_mem_copy_create, op_prg_mem_free, pktSize);
				op_pk_nfd_set(pkt, "PrevHop", aodv_myAddr);
				op_pk_nfd_set(pkt, "DestCount", myDestCount);
				op_pk_nfd_set(pkt, "UnreachableDestinations", unreachableDestsPk);
				
				assert(*myAddrListPtr != aodv_myAddr);
				
				
				if (precursorCount == 1)
					{
						aodv_pk_send_to_mac(pkt, rerrDest);
						dbg_print(1, "Relayed RERR to node %i (unicast) with %i entries\n", rerrDest, myDestCount);
					}
				else 
					{
						aodv_pk_send_to_mac(pkt, AODV_BROADCAST_ADDR);
						dbg_print(1, "Relayed RERR (broadcast) with %i entries\n", myDestCount);
					}
			}
		else
			{
				dbg_print(1, "Destroyed RERR (no need to forward)\n");
				op_pk_destroy(pkt);
				op_pk_destroy(unreachableDestsPk);
				op_prg_mem_free(myAddrListPtr);
			}
		
		op_prg_mem_free(addrListPtr);
		
		aodv_rte_dbg_print(1);
	}

/**
 * process a RREP_ACK packet
 */
void aodv_handle_pk_rrep_ack(Packet* pkt)
	{
		//
		assert(FALSE);
	}



/**
 * process a DATA packet
 */
void aodv_handle_pk_data(Packet* pkt)
	{
		AodvT_Address destAddr;
		AodvT_Address originAddr;
		AodvT_Address prevHop;
		int ttl;
		AodvT_rte* rte_d = NULL;	// dest
		AodvT_rte* rte_o = NULL;	// origin
		AodvT_rte* rte_p = NULL;	// prev
		AodvT_rte* rte_n = NULL;	// next
		BOOL generateRERR = FALSE;
		int					stat_id;
		
		op_pk_nfd_get(pkt, "STAT_ID" , 		&stat_id);
		
		op_pk_nfd_get(pkt, "Dest_IPAddr", 	&destAddr);
		op_pk_nfd_get(pkt, "Origin_IPAddr", &originAddr);
		op_pk_nfd_get(pkt, "PrevHop", 		&prevHop);
		op_pk_nfd_get(pkt, "TTL", 			&ttl);
		
		
		dbg_print(1, "Received DATA packet: origin %i, dest %i, prevHop %i\n", originAddr, destAddr, prevHop);
		
		ttl--;
		
		/*	6.2
			Each time a route is used to forward a data packet, its Active Route
			Lifetime field of the source, destination and the next hop on the
			path to the destination is updated to be no less than the current
			time plus ACTIVE_ROUTE_TIMEOUT.  Since the route between each
			originator and destination pair is expected to be symmetric, the
			Active Route Lifetime for the previous hop, along the reverse path
			back to the IP source, is also updated to be no less than the current
			time plus ACTIVE_ROUTE_TIMEOUT.  The lifetime for an Active Route is
			updated each time the route is used regardless of whether the
			destination is a single node or a subnet.
		*/
		
		// update lifetime of origin node
		rte_o = aodv_rte_get(originAddr);
		if (rte_o != NULL && rte_o->routeValid)
			{
				aodv_rte_update_lifetime(rte_o, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
			}
		// else there is a uni-directional link => RERR when answer follows
		
		// update lifetime of previous hop node
		rte_p = aodv_rte_get(prevHop);
		if (rte_p != NULL && rte_p->routeValid)
			{
				aodv_rte_update_lifetime(rte_p, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
			}
		// else there is a uni-directional link => RERR when answer follows
		
		//Adds my id as forwarder
		if (strlen(stats_data_pk [stat_id].route) < 45)		
			sprintf(stats_data_pk [stat_id].route, "%s | %d ", stats_data_pk [stat_id].route , aodv_myAddr);
			
		if (destAddr != aodv_myAddr)
			{
				// get destination RTE
				rte_d = aodv_rte_get(destAddr);
				generateRERR = (NULL == rte_d || !rte_d->routeValid);
				
				// get next hop RTE
				if (!generateRERR)
					{
						rte_n = aodv_rte_get(rte_d->nextHopAddr);
						//assert(NULL != rte_n && rte_n->routeValid);
						//generateRERR = (NULL == rte_n || !rte_n->routeValid);
					}
				
				if (generateRERR)
					{		
						if (NULL != rte_d && rte_d->routeValid)
							{
								aodv_rte_invalidate_route(rte_d);
							}
							 
						aodv_pk_send_rerr(destAddr);
						
						op_pk_destroy(pkt); // data packet is lost
						// TODO: initiate repair?
					}
				else if (NULL != rte_n && rte_n->routeValid)
					{
						// route is valid
					
						assert(rte_d != NULL && rte_n != NULL);
						
						aodv_rte_precursors_add(rte_d, prevHop);
						aodv_rte_precursors_add(rte_n, prevHop);
						
						if (!aodv_rte_precursors_is_precursor(rte_d, prevHop))
							{
								aodv_rte_dbg_print(100);
								assert(0);
							}
						
						aodv_rte_update_lifetime(rte_d, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
						aodv_rte_update_lifetime(rte_n, op_sim_time() + AODV_ACTIVE_ROUTE_TIMEOUT);
		
						if (ttl > 0) // essentially IP functionality
							{
								// relay data packet
								op_pk_nfd_set(pkt, "PrevHop", aodv_myAddr);
								op_pk_nfd_set(pkt, "TTL", ttl);
				
								aodv_pk_send_to_mac(pkt, rte_d->nextHopAddr);
								
								dbg_print(1, "DATA relayed to node %i\n", rte_d->nextHopAddr);
								
								aodv_rte_dbg_print(1);				

							}
						else
							{
								// destroy it, TTL expired
								op_pk_destroy(pkt);
							}
					}
			}
		else
			{
				dbg_print(1, "DATA packet for me!\n");
//				aodv_rte_dbg_print(1);
				
				
				
				// stats
				stats_data_pk	[stat_id].hops		 		= MAX_NETWORK_RADIUS - ttl;
				stats_data_pk	[stat_id].time_reception 	= op_sim_time();
				stats_data_pk	[stat_id].pk_size			= op_pk_bulk_size_get(pkt);
				op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stat_id].dest_x_pos));	
				op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stat_id].dest_y_pos));	

				
				op_pk_destroy(pkt);
			}

	}


void aodv_handle_timeout_route_discovery(AodvT_rte* rte)
	{	
		int aodv_ttl_value;
		double timeoutDelta;
	
		assert(rte->routeDiscovery && !rte->routeValid);
	
		aodv_ttl_value = rte->lastTtl + AODV_TTL_INCREMENT;
		if (aodv_ttl_value < AODV_TTL_THRESHOLD)
			{
				// continue expanding ring search
			
				/*	6.4. Controlling Dissemination of Route Request Messages

					To prevent unnecessary network-wide dissemination of RREQs, the
					originating node SHOULD use an expanding ring search technique.  In
					an expanding ring search, the originating node initially uses a TTL =
					TTL_START in the RREQ packet IP header and sets the timeout for
					receiving a RREP to RING_TRAVERSAL_TIME milliseconds.
					RING_TRAVERSAL_TIME is calculated as described in section 10.  The
					TTL_VALUE used in calculating RING_TRAVERSAL_TIME is set equal to the
					value of the TTL field in the IP header.  If the RREQ times out
					without a corresponding RREP, the originator broadcasts the RREQ
					again with the TTL incremented by TTL_INCREMENT.  This continues
					until the TTL set in the RREQ reaches TTL_THRESHOLD, beyond which a
					TTL = NET_DIAMETER is used for each attempt.  Each time, the timeout
					for receiving a RREP is RING_TRAVERSAL_TIME.  When it is desired to
					have all retries traverse the entire ad hoc network, this can be
					achieved by configuring TTL_START and TTL_INCREMENT both to be the
					same value as NET_DIAMETER.

					The Hop Count stored in an invalid routing table entry indicates the
					last known hop count to that destination in the routing table.  When
					a new route to the same destination is required at a later time
					(e.g., upon route loss), the TTL in the RREQ IP header is initially
					set to the Hop Count plus TTL_INCREMENT.  Thereafter, following each
					timeout the TTL is incremented by TTL_INCREMENT until TTL =
					TTL_THRESHOLD is reached.  Beyond this TTL = NET_DIAMETER is used.
					Once TTL = NET_DIAMETER, the timeout for waiting for the RREP is set
					to NET_TRAVERSAL_TIME, as specified in section 6.3.

					An expired routing table entry SHOULD NOT be expunged before
					(current_time + DELETE_PERIOD) (see section 6.11).  Otherwise, the
					soft state corresponding to the route (e.g., last known hop count)
					will be lost.  Furthermore, a longer routing table entry expunge time
					MAY be configured.  Any routing table entry waiting for a RREP SHOULD
					NOT be expunged before (current_time + 2 * NET_TRAVERSAL_TIME).
				*/
			
				aodv_pk_send_rreq(rte->destAddr, aodv_ttl_value);
				rte->lastTtl = aodv_ttl_value;
				
				timeoutDelta = AODV_RING_TRAVERSAL_TIME;
				
				aodv_rte_update_lifetime(rte, op_sim_time() + 2*timeoutDelta);
				
				rte->routeDiscoveryTimeout = op_intrpt_schedule_self(
					op_sim_time() + timeoutDelta, TIMEOUT_ROUTE_DISCOVERY_CODE);
				
				dbg_print(1, "Route discovery for node %i (ring search radius: %i hops)\n", rte->destAddr, rte->lastTtl);
			}
		else
			{
				// RREQ at full range (NET_DIAMETER)
			
				rte->lastTtl = AODV_NET_DIAMETER;
			
				/*	6.3
					After broadcasting a RREQ, a node waits for a RREP (or
					other control message with current information regarding a route to
					the appropriate destination).  If a route is not received within
					NET_TRAVERSAL_TIME milliseconds, the node MAY try again to discover a
					route by broadcasting another RREQ, up to a maximum of RREQ_RETRIES
					times at the maximum TTL value.  Each new attempt MUST increment and
					update the RREQ ID.  For each attempt, the TTL field of the IP header
					is set according to the mechanism specified in section 6.4, in order
					to enable control over how far the RREQ is disseminated for the each
					retry.
				*/
		
				rte->rreqRetries++;
		
				if (rte->rreqRetries <= AODV_RREQ_RETRIES)
					{
						aodv_pk_send_rreq(rte->destAddr, AODV_NET_DIAMETER); 
				
						/*	6.3
							To reduce congestion in a network, repeated attempts by a source node
							at route discovery for a single destination MUST utilize a binary
							exponential backoff.  The first time a source node broadcasts a RREQ,
							it waits NET_TRAVERSAL_TIME milliseconds for the reception of a RREP.
							If a RREP is not received within that time, the source node sends a
							new RREQ.  When calculating the time to wait for the RREP after
							sending the second RREQ, the source node MUST use a binary
							exponential backoff.  Hence, the waiting time for the RREP
							corresponding to the second RREQ is 2 * NET_TRAVERSAL_TIME
							milliseconds.  If a RREP is not received within this time period,
							another RREQ may be sent, up to RREQ_RETRIES additional attempts
							after the first RREQ.  For each additional attempt, the waiting time
							for the RREP is multiplied by 2, so that the time conforms to a
							binary exponential backoff.
						*/
						
						timeoutDelta = (1 << (rte->rreqRetries - 1)) * AODV_NET_TRAVERSAL_TIME;
						
						aodv_rte_update_lifetime(rte, op_sim_time() + 2*timeoutDelta);
				
						rte->routeDiscoveryTimeout = op_intrpt_schedule_self(
							op_sim_time() + timeoutDelta, TIMEOUT_ROUTE_DISCOVERY_CODE);
						
						dbg_print(1, "Route discovery for node %i (retries: %i)\n", rte->destAddr, rte->rreqRetries);
						assert(rte->routeDiscovery);
					}
				else
					{
						/*	6.3
							If a route discovery has been
							attempted RREQ_RETRIES times at the maximum TTL without receiving any
							RREP, all data packets destined for the corresponding destination
							SHOULD be dropped from the buffer and a Destination Unreachable
							message SHOULD be delivered to the application.
						*/
			
						dbg_print(100, "Route discovery for node %i FAILED (destination unreachable)\n", rte->destAddr);
						
						assert(!rte->routeValid);
						rte->routeDiscovery = FALSE;
						rte->rreqRetries = 0;
						aodv_rte_update_lifetime(rte, op_sim_time() + AODV_DELETE_PERIOD);
				
						while (op_prg_list_size(rte->queuedPackets) > 0)
							{
								op_prg_mem_free(op_prg_list_remove(rte->queuedPackets, OPC_LISTPOS_HEAD));
							}
					}
			}
	}

/**
 * initiate a RREQ request series
 *
 * @parm rte			RTE for which a RREQ has to be sent
 * @parm aodv_ttl_value	Initial TTL value
 */
void aodv_initiate_rreq(AodvT_rte* rte, int aodv_ttl_value)
	{
		double timeout;
	
		assert(!rte->routeDiscovery);
		assert(!rte->routeValid);
		
		/*	6.4. Controlling Dissemination of Route Request Messages

			To prevent unnecessary network-wide dissemination of RREQs, the
			originating node SHOULD use an expanding ring search technique.  In
			an expanding ring search, the originating node initially uses a TTL =
			TTL_START in the RREQ packet IP header and sets the timeout for
			receiving a RREP to RING_TRAVERSAL_TIME milliseconds.
			RING_TRAVERSAL_TIME is calculated as described in section 10.  The
			TTL_VALUE used in calculating RING_TRAVERSAL_TIME is set equal to the
			value of the TTL field in the IP header.  If the RREQ times out
			without a corresponding RREP, the originator broadcasts the RREQ
			again with the TTL incremented by TTL_INCREMENT.  This continues
			until the TTL set in the RREQ reaches TTL_THRESHOLD, beyond which a
			TTL = NET_DIAMETER is used for each attempt.  Each time, the timeout
			for receiving a RREP is RING_TRAVERSAL_TIME.  When it is desired to
			have all retries traverse the entire ad hoc network, this can be
			achieved by configuring TTL_START and TTL_INCREMENT both to be the
			same value as NET_DIAMETER.

			The Hop Count stored in an invalid routing table entry indicates the
			last known hop count to that destination in the routing table.  When
			a new route to the same destination is required at a later time
			(e.g., upon route loss), the TTL in the RREQ IP header is initially
			set to the Hop Count plus TTL_INCREMENT.  Thereafter, following each
			timeout the TTL is incremented by TTL_INCREMENT until TTL =
			TTL_THRESHOLD is reached.  Beyond this TTL = NET_DIAMETER is used.
			Once TTL = NET_DIAMETER, the timeout for waiting for the RREP is set
			to NET_TRAVERSAL_TIME, as specified in section 6.3.

			An expired routing table entry SHOULD NOT be expunged before
			(current_time + DELETE_PERIOD) (see section 6.11).  Otherwise, the
			soft state corresponding to the route (e.g., last known hop count)
			will be lost.  Furthermore, a longer routing table entry expunge time
			MAY be configured.  Any routing table entry waiting for a RREP SHOULD
			NOT be expunged before (current_time + 2 * NET_TRAVERSAL_TIME).
		*/
					
		rte->routeDiscovery = TRUE;
		rte->rreqRetries = 0;
		aodv_rte_update_lifetime(rte, op_sim_time() + 2*AODV_NET_TRAVERSAL_TIME);
						
		if (AODV_NET_DIAMETER <= aodv_ttl_value)
			{
				aodv_ttl_value = AODV_NET_DIAMETER;
				timeout = AODV_NET_TRAVERSAL_TIME;
			}	
		else
			{
				timeout = AODV_RING_TRAVERSAL_TIME; // macro uses aodv_ttl_value!
			}
						
		rte->lastTtl = aodv_ttl_value;
						
		aodv_pk_send_rreq(rte->destAddr, aodv_ttl_value); 
		rte->routeDiscoveryTimeout = op_intrpt_schedule_self(op_sim_time() + timeout, 
			TIMEOUT_ROUTE_DISCOVERY_CODE);
		
		dbg_print(2, "Initiated RREQ for node %i, TTL %i\n", rte->destAddr, aodv_ttl_value);
	}

/**
 * send a data packet or queue it if there is no route
 */
void aodv_pk_data_enqueue(AodvT_Address destAddr)
	{
		AodvT_datapk_queue_entry* dqe;
		AodvT_rte* rte;
		
		int aodv_ttl_value = AODV_TTL_START;
		

		// True stats (following the scheme of VSR, CBRP, OLSR...)
		stats_data_pk	[stats_nb_data_pk].source			= aodv_myAddr;
		stats_data_pk	[stats_nb_data_pk].dest				= destAddr;
		stats_data_pk 	[stats_nb_data_pk].time_generation	= op_sim_time();
		op_ima_obj_attr_get(op_id_parent(op_id_self()) , "x position", &(stats_data_pk	[stats_nb_data_pk].src_x_pos));	
		op_ima_obj_attr_get(op_id_parent(op_id_self()) , "y position", &(stats_data_pk	[stats_nb_data_pk].src_y_pos));	
		sprintf(stats_data_pk	[stats_nb_data_pk].route, "%d ", aodv_myAddr);
		if (stats_nb_data_pk == MAX_DATA_PK-1-1)
			op_sim_end("We have too many DATA pk", "please increase MAX_NB_DATA_PK","","");
	
		
		//The entry in the routing table
		rte = aodv_rte_get(destAddr);

		
		if (NULL != rte && rte->routeValid)
			{
				// send it
				aodv_pk_data_send(destAddr , stats_nb_data_pk);
				dbg_print(1, "DATA: Sent data packet immediatly to node %i (route exists)\n", destAddr);
			}
		else 
			{
				// send RREQ
				if (NULL == rte)
					rte = aodv_rte_create(destAddr);
				else
					{
						aodv_ttl_value = rte->hopCount + AODV_TTL_INCREMENT;
					}
				
				if (!rte->routeDiscovery)
					{	
						aodv_initiate_rreq(rte, aodv_ttl_value);
					}
				else
					{
						assert(op_ev_valid(rte->routeDiscoveryTimeout));
					}
				
				// queue packet to resend it later
				dqe = op_prg_mem_alloc(sizeof(AodvT_datapk_queue_entry));
				dqe->destAddr 	= destAddr;
				dqe->sendTime 	= op_sim_time();
				dqe->stat_id 	= stats_nb_data_pk;
				op_prg_list_insert(rte->queuedPackets, dqe, OPC_LISTPOS_TAIL);
				
				dbg_print(1, "DATA: Queued data packet to node %i (route does not exist)\n", destAddr);
			}
		stats_nb_data_pk++;
	}

/**
 * maintain route table
 */
void aodv_rte_maintain()
	{
		AodvT_rte* rte;
		int i = 0;
		
		while (op_prg_list_size(aodv_RT) > i) 
			{
				rte = op_prg_list_access(aodv_RT, i);
				assert(rte);
				
				if (rte->routeValid && rte->lifetime < op_sim_time())
					{	
						//dbg_print(1, "Invalidating RTE for node %i\n", rte->destAddr);
						aodv_rte_invalidate_route(rte);
						rte->lifetime = rte->lifetime + AODV_DELETE_PERIOD;
						//aodv_rte_update_lifetime(rte, rte->lifetime + AODV_DELETE_PERIOD);
					}

				if (!rte->routeValid && rte->lifetime < op_sim_time()) 
					{
						// remove entry completely (delete period expired)
						//dbg_print(1. "Deleting RTE for node %i (expired %1.8f)\n", rte->destAddr, rte->lifetime);
					
						// only if we are not in a discovery process
						if (!rte->routeDiscovery)
							{	
								aodv_rte_remove(rte->destAddr);
								rte = NULL;
							}
						else
							{
								assert(FALSE);
								/*
								// prolongate lifetime
								while (rte->lifetime < op_sim_time())
									{
										rte->lifetime = rte->lifetime + AODV_DELETE_PERIOD;
									}
								*/
							}
					}
				else
					{
						i++;
					}
				
				assert(rte == NULL || !rte->routeValid || (rte->hopCount > 0 && (rte->hopCount == 1 || rte->destAddr != rte->nextHopAddr)));
			}
		
	}


/**
 * print statistics
 */
void aodv_stats_node_print()
	{
		dbg_print(100, "pkRREQ %i, pkRREP %i, pkRERR %i, pkRREP_ACK %i\n", 
			aodv_stats.pkRREQ, aodv_stats.pkRREP, aodv_stats.pkRERR, aodv_stats.pkRREP_ACK);
		dbg_print(100, "pkDataSent %i, pkDataRecvd %i\n", 
			aodv_stats.pkDataSent, aodv_stats.pkDataRecvd);
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
	void aodv_process (void);
	Compcode aodv_process_init (void **);
	void aodv_process_diag (void);
	void aodv_process_terminate (void);
	void aodv_process_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
aodv_process (void)
	{
	int _block_origin = 0;
	FIN (aodv_process ());
	if (1)
		{


		FSM_ENTER (aodv_process)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init2) enter executives **/
			FSM_STATE_ENTER_FORCED (0, state0_enter_exec, "init2", "aodv_process () [init2 enter execs]")
				{
				//CONTROL
				char		str[150];
				char		var_name[200];
				int			i;
				//TOPOLOGY
				int			nb_fixed_nodes , nb_mobile_nodes , is_node_AP;
				//AP Position
				int			process_id , node_id;
				double		XMAX , YMAX;
				int			MOBILITY_MODEL;
				
				
				
				
				//----------------------------------------------------
				//
				//					My address
				//
				//-----------------------------------------------------
				
				// get our address (use WLAN-MAC address)
				op_ima_obj_attr_get(op_topo_parent(op_id_self()), 	"Wireless LAN MAC Address", &aodv_myAddr);
				op_ima_obj_attr_get(op_id_self(), 					"is_AP", 					&is_AP);
				assert(aodv_myAddr >= 0);
				
				
				
				
				//----------------------------------------------------
				//
				//					TOPOLOGY
				//
				//-----------------------------------------------------
				
				
				if (is_AP)
					nb_aps++;
				my_stat_id = nb_nodes++;
				
				
				//Initialize the constant about Energy
				if (my_stat_id == 0)
					{
						//For file names (debug and statistics)
						begin_time_for_filenames = time(NULL);
				
						
						//NB :   AP / normal nodes
						nb_fixed_nodes 		= op_topo_object_count(OPC_OBJTYPE_NDFIX);
						for(i=0 ; i<nb_fixed_nodes ; i++)
							{
								node_id = op_topo_object( OPC_OBJTYPE_NDFIX , i);
								sprintf(var_name , "%s.is_AP" , PROCESS_NAME);
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
								sprintf(var_name , "%s.is_AP" , PROCESS_NAME);
								op_ima_obj_attr_get(node_id, var_name ,	&is_node_AP); 
								if (is_node_AP)
									nb_aps_expected++;
								else
									nb_nodes_expected++;
							}
					}
						
						
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
				
				begin_time_for_filenames = time(NULL);
				
				
				
				
				
				//--------------- Global periodic stats ------------
				
				if (my_stat_id==1)
					{
						//Stats About Data Packets
						for(i=0; i < MAX_DATA_PK ; i++)
							{
								stats_data_pk [i].source 			= 0;
								stats_data_pk [i].dest 				= 0;
								stats_data_pk [i].pk_size			= 0;
								stats_data_pk [i].hops 				= 0;
								stats_data_pk [i].nb_retry 			= 0;
								stats_data_pk [i].nb_repairs		= 0;
								stats_data_pk [i].time_emission 	= 0;
								stats_data_pk [i].time_reception 	= 0;
								stats_data_pk [i].method		 	= 0;
							}
						//Stats About RREQ/RREP
						for(i=0; i < MAX_RREQ_PK ; i++)
							{
								stats_rreq [i].source 				= 0;
								stats_rreq [i].dest 				= 0;
								stats_rreq [i].rreq_time_emission 	= 0;
								stats_rreq [i].rreq_time_reception 	= 0;
								stats_rreq [i].rreq_nb_retry 		= 0;
								stats_rreq [i].rrep_time_emission 	= 0;
								stats_rreq [i].rrep_time_reception 	= 0;
								stats_rreq [i].rrep_hops			= 0;
								stats_rreq [i].rrep_nb_retry 		= 0;
							}
				
					}
				
				
				
				//----------------------------------------------------
				//
				//			LISTS INTIALIZATIONS
				//
				//-----------------------------------------------------
				
				
				ack_table 		=  op_prg_list_create();
				ici_list		= op_prg_list_create();
				
				
				
				
				
				//----------------------------------------------------
				//
				//			GENERAL DEBUG FILE
				//
				//-----------------------------------------------------
				
				if (!aodvOut)
					{
						if (DEBUG)
							{
								char s[512];
								sprintf(s, "results_aodv\\aodvOut.txt");
								aodvOut = fopen(s, "w");
								if (!aodvOut)
									{
										printf("Cannot open %s\n", s);
										assert(0);
									}
								fprintf(aodvOut, "AODV first time init\n");
							}
						
					}
				
				aodvUseCount++;
				
				
				
				//----------------------------------------------------
				//
				//			PARAMETERS
				//
				//-----------------------------------------------------
				
				
				
				// increase number of nodes
				aodv_node_count++;
				
				
				// some configuration parameters
				//assert(op_ima_obj_attr_get(op_id_self(), "WLAN Acks", 					&aodv_config_wlan_ack) 				== OPC_COMPCODE_SUCCESS);
				//assert(op_ima_obj_attr_get(op_id_self(), "WLAN Promiscuous Mode", 		&aodv_config_wlan_promiscuous_mode) == OPC_COMPCODE_SUCCESS);
				//assert(op_ima_obj_attr_get(op_id_self(), "Maintain local connectivity",	&aodv_config_passive_ack)			== OPC_COMPCODE_SUCCESS);
				//assert(op_ima_obj_attr_get(op_id_self(), "Hello Messages",				&aodv_config_hellos)				== OPC_COMPCODE_SUCCESS);
				aodv_config_wlan_ack 				= OPC_FALSE;
				aodv_config_wlan_promiscuous_mode 	= OPC_FALSE;
				aodv_config_passive_ack				= OPC_FALSE;
				aodv_config_hellos					= OPC_FALSE;
				
				dbg_print(100, "CONFIG: maintaining local connectivity (passive ACKs, chapter 6.10): %i\n", aodv_config_passive_ack);
				
				if (aodv_config_passive_ack)
					{
						dbg_print(100, "CONFIG: using WLAN ACKs: %i\n", 				aodv_config_wlan_ack);
						dbg_print(100, "CONFIG: using WLAN promiscuous mode: %i\n", 	aodv_config_wlan_promiscuous_mode);
						if (aodv_config_wlan_ack && aodv_config_wlan_promiscuous_mode)
							dbg_print(100, "CONFIG: WARNING: using WLAN promiscuous mode unnecessary when using WLAN ACKs\n");
						if (!aodv_config_wlan_ack && !aodv_config_wlan_promiscuous_mode)
							dbg_print(100, "CONFIG: WARNING: neither using WLAN promiscuous mode nor WLAN ACKs => unicast RREQ for data packets used (NOT suggested)\n");
					}
				
				// create various structures
				aodv_RT = op_prg_list_create();
				aodv_RREQs = op_prg_list_create();
				aodv_ack_wait = op_prg_list_create();
				
				memset(&aodv_stats, 0, sizeof(aodv_stats));
				
				// data flow simulation attributes
				
				assert(op_ima_sim_attr_get(OPC_IMA_INTEGER, "DATA_PK_SIZE", 			&DATA_PK_SIZE) 				== OPC_COMPCODE_SUCCESS);
				assert(op_ima_sim_attr_get(OPC_IMA_INTEGER, "NB_CONNECTIONS", 			&NB_CONNECTIONS) 			== OPC_COMPCODE_SUCCESS);
				assert(op_ima_sim_attr_get(OPC_IMA_DOUBLE, 	"INTERARRIVAL_DATA_PK", 	&INTERARRIVAL_DATA_PK) 		== OPC_COMPCODE_SUCCESS);
				assert(op_ima_sim_attr_get(OPC_IMA_INTEGER, "NB_PK_PER_FLOW", 			&NB_PK_PER_FLOW) 			== OPC_COMPCODE_SUCCESS);
				
				assert(DATA_PK_SIZE > 0);
				assert(NB_CONNECTIONS >= 0);
				assert(INTERARRIVAL_DATA_PK > 0.0);
				assert(NB_PK_PER_FLOW > 0);
				
				
				dbg_print(100, "CONFIG: Data Flow: packet size: %i bytes\n", 			DATA_PK_SIZE);
				dbg_print(100, "CONFIG: Data Flow: number of flows: %i\n", 				NB_CONNECTIONS);
				dbg_print(100, "CONFIG: Data Flow: packet interarrival time: %1.2fs\n", INTERARRIVAL_DATA_PK);
				dbg_print(100, "CONFIG: Data Flow: packets per flow: %i\n", 			NB_PK_PER_FLOW);
				
				
				
				
				
				
				//----------------------------------------------------
				//
				//			NEXT INTERRUPTIONS
				//
				//-----------------------------------------------------
				
				
				
				aodv_flowgen_ici = op_ici_create("aodv_flowgen");
				
				if (aodv_pkt_flow_count < NB_CONNECTIONS)
					{
						op_intrpt_schedule_self(TIME_BEGIN_DATA + op_dist_uniform(INTERARRIVAL_DATA_PK * NB_PK_PER_FLOW), 
							GENERATE_PKT_FLOW_CODE);
						aodv_pkt_flow_count++;
					}
				
				if (aodv_config_hellos)
					{
						op_intrpt_schedule_self(op_sim_time() + op_dist_uniform(AODV_HELLO_INTERVAL), SEND_HELLO_CODE);
						bc_during_hello_interval = FALSE;
					}
				
				}


			/** state (init2) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init2", "aodv_process () [init2 exit execs]")
				{
				}


			/** state (init2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init2", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, state1_enter_exec, "idle", "aodv_process () [idle enter execs]")
				{
				
				int i;
				AodvT_rte* rte;
				AodvT_rte* rte_n;
				AodvT_datapk_queue_entry* dpe;
				
				//fprintf(aodvOut, "%d: Entering idle state executive\n", aodv_myAddr);
				
				// send queued data packets, if necessary
				
				
				for (i = 0; i < op_prg_list_size(aodv_RT); i++)
					{
						rte = op_prg_list_access(aodv_RT, i);
						if (rte->routeValid)
							{	
								if (aodv_config_passive_ack)
									{
										// use passive acknowledgements, so always wait for an ACK for a data packet
										if (op_prg_list_size(rte->queuedPackets) > 0)
											{
												// check, if next hop was acknowledged (or, at least, if we do not wait an Ack)
												BOOL acknowledged = FALSE;
										
												if (rte->destAddr == rte->nextHopAddr)
													acknowledged = rte->acknowledged;
												else
													{
														rte_n = aodv_rte_get(rte->nextHopAddr);
														assert(rte_n != NULL && rte_n->routeValid);
														acknowledged = rte_n->acknowledged;
													}	
										
												if (acknowledged)
													{
														dpe = op_prg_list_remove(rte->queuedPackets, OPC_LISTPOS_HEAD);
										
														if (dpe->sendTime >= op_sim_time()-TIMEOUT_DATA_PK_IN_BUFFER)
															aodv_pk_data_send(dpe->destAddr, dpe->stat_id);
														
														dbg_print(1, "DATA: Sent queued data packet to node %i\n", dpe->destAddr);
														op_prg_mem_free(dpe);
													}
											}
									}
								else
									{
										// never wait for an ACK, sent all data that is left
										while (op_prg_list_size(rte->queuedPackets) > 0)
											{
												dpe = op_prg_list_remove(rte->queuedPackets, OPC_LISTPOS_HEAD);
										
												if (dpe->sendTime >= op_sim_time()-TIMEOUT_DATA_PK_IN_BUFFER)
													aodv_pk_data_send(dpe->destAddr, dpe->stat_id);
												
												dbg_print(1, "DATA: Sent queued data packet to node %i\n", dpe->destAddr);
												op_prg_mem_free(dpe);
											}
									}
							}
					}
				
				
				//Delete all timeouted entries in the list of ICI (for mac layer communications)
				delete_timeout_in_ici_list();
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,aodv_process)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "aodv_process () [idle exit execs]")
				{
				
				// cleanups
				//fprintf(aodvOut, "Cleanups\n");
				aodv_rte_maintain();
				aodv_rreqs_maintain();
				
				/*
				dbg_print("intrpt_type %i, intrpt_code %i, OPC_INTRPT_REMOTE %i\n", 
					op_intrpt_type(), op_intrpt_code(), OPC_INTRPT_REMOTE);
				*/
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (END_SIM)
			FSM_TEST_COND (PKT_FROM_MAC_LAYER)
			FSM_TEST_COND (PKT_FROM_HIGHER_LAYER)
			FSM_TEST_COND (TIMEOUT_ROUTE_DISCOVERY)
			FSM_TEST_COND (GENERATE_PKT_FLOW)
			FSM_TEST_COND (ACK_FROM_MAC_LAYER)
			FSM_TEST_COND (TIMEOUT_ACK)
			FSM_TEST_COND (TIMEOUT_HELLO)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 3, state3_enter_exec, ;, "END_SIM", "", "idle", "end")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "PKT_FROM_MAC_LAYER", "", "idle", "mac_layer")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "PKT_FROM_HIGHER_LAYER", "", "idle", "higher_layer")
				FSM_CASE_TRANSIT (3, 6, state6_enter_exec, ;, "TIMEOUT_ROUTE_DISCOVERY", "", "idle", "route_discovery")
				FSM_CASE_TRANSIT (4, 7, state7_enter_exec, ;, "GENERATE_PKT_FLOW", "", "idle", "generate_pk_flow")
				FSM_CASE_TRANSIT (5, 8, state8_enter_exec, ;, "ACK_FROM_MAC_LAYER", "", "idle", "mac_ack")
				FSM_CASE_TRANSIT (6, 9, state9_enter_exec, ;, "TIMEOUT_ACK", "", "idle", "ack_timeout")
				FSM_CASE_TRANSIT (7, 10, state10_enter_exec, ;, "TIMEOUT_HELLO", "", "idle", "send_hello")
				FSM_CASE_TRANSIT (8, 1, state1_enter_exec, ;, "default", "", "idle", "idle")
				}
				/*---------------------------------------------------------*/



			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (2, "init", "aodv_process () [init enter execs]")
				{
				// synchronisation with lower levels
				op_intrpt_schedule_self(op_sim_time() + TIME_INIT_MAC, 0);
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,aodv_process)


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "init", "aodv_process () [init exit execs]")
				{
				}


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "init", "init2")
				/*---------------------------------------------------------*/



			/** state (end) enter executives **/
			FSM_STATE_ENTER_UNFORCED (3, state3_enter_exec, "end", "aodv_process () [end enter execs]")
				{
				
				//----------------------------------------------------------------
				//				SIMULATION END
				//----------------------------------------------------------------
				
				//Collects some stats when the simulation ends
				//CONTROL
					char	filename[60];
					FILE	*file , *data_file , *rreq_file , *rrep_file , *rerr_file;
					int 	i , j;
					int		node_id , cdcl_id;
					char	msg[150];
				//AP HELLOS
					double	ap_hellos_rcvd_total					= 0; 
				//AP REG
					int		nb_sent_ap_reg							= 0;
					int		nb_received_ap_reg						= 0;
					int		hops_ap_reg								= 0;
					int		nb_retransmissions_ap_reg				= 0;
					double	delay_ap_reg							= 0;
				//DURATION
					double	stats_time_duration;
				//PACKETS
					double	nb_routing_pk_total						= 0;
					double	nb_routing_bits_total					= 0;
				//DATA
					double	delay_data_pk 							= 0;
					int		nb_data_pk								= 0;
					int		nb_data_pk_sent							= 0;
					int		nb_data_pk_received						= 0;
					int		throughput_data_pk						= 0;
					int		hops_data_pk							= 0;
					int		nb_retransmissions_data_pk				= 0;
					double	tmp_distance							= 0;
					int		length_distribution	[MAX_NETWORK_RADIUS];
				//SPEED
				   	double	SPEED_HIGH_MIN 							= 0;
				   	double	SPEED_HIGH_MAX 							= 0;
				   	double	SPEED_LOW_MIN 							= 0;
				   	double	SPEED_LOW_MAX 							= 0;
					int		speed_class								= 0;
				//TOPOLOGY
					double	X_MAX									= 0;
					double	Y_MAX									= 0;
				//RREQ
					int		nb_rreq_sent							= 0;
					int		nb_retry_for_rreq						= 0;
					int		nb_retry_for_success_rreq				= 0;
					int		nb_success_rreq_with_non_null_nb_retry	= 0;
				//RREP
					int		nb_rrep_received						= 0;
					int		nb_rrep_transmitted						= 0;
					double	average_delay_for_rrep					= 0;
					double	average_delay_for_rreq_to_final_rrep	= 0;
					int		average_nb_retransmissions_rrep 		= 0;
					int		hops_rrep								= 0;
				//RERR
					int		nb_rerr_sent							= 0;
					int		nb_rerr_received						= 0;
					int		nb_retry_for_rerr						= 0;
					double	average_delay_for_rerr					= 0;
					int		average_nb_retransmissions_rerr 		= 0;
					int		hops_rerr								= 0;
				//OVERHEADS
					int		*overhead_tmp_cdcl_cds_pk				;
					int		*overhead_tmp_cdcl_cluster_pk			;
					int		*overhead_tmp_cdcl_hello_pk				;
					int		*overhead_tmp_cdcl_cds_bits				;
					int		*overhead_tmp_cdcl_cluster_bits			;
					int		*overhead_tmp_cdcl_hello_bits			;
				
				
				
				
				
				dbg_print(100, "END_SIM\n");
				
				aodv_rte_dbg_print(100);
				aodv_stats_node_print();
				
				aodvUseCount--;
				
				/*if (aodvOut && aodvUseCount == 0)
					{
						fprintf(aodvOut, "End of simulation.\n");
						
						aodv_stats_print();
						
						fclose(aodvOut);
						aodvOut = 0;
					}
				*/
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				//Stats Per node
				//	individual_statistics_generate();
					
				//Speeds
					if (op_ima_obj_attr_exists(op_topo_parent(op_id_self()), "mobility.Speed_Class") == OPC_TRUE)
						{
							op_ima_obj_attr_get(op_topo_parent(op_id_self()), "mobility.Speed_Class", &speed_class);
							switch(speed_class)		
								{
									case LOW_SPEED :
										nb_loc_low_speed_nodes++;
									break;
									case HIGH_SPEED :
										nb_loc_high_speed_nodes++;
									break;
								}
						}
				
				
					//-----------------------
					//    CDCL OVERHEADS 
					//-----------------------
					node_id = op_topo_parent(op_id_self());
					cdcl_id = op_id_from_name(node_id, OPC_OBJTYPE_PROC , "cds-cluster");
				
				
				
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
							if (DEBUG_DATA >= LOW)
								{
									sprintf(filename,"results_aodv/%d_aodv_debug_pk_data.txt" , begin_time_for_filenames);		
									data_file = fopen(filename , "w");
									fprintf(data_file,"#SRC	|	DEST	|	SIZE	|	HOPS	|	RETRY	|REPAIRS	|	SENT		|	RECEIVED	|	DELAY		|	METHOD|	GENERATION	|	DISTANCE	|	ROUTE\n");	
								}
							for (i=0 ;  i < stats_nb_data_pk ; i++ )
								{
									//The pk is effective (valid final_dest...)
									if (stats_data_pk [i].time_generation != -1)
										{
											nb_data_pk++;
										}
									
									if (stats_data_pk [i].time_emission != 0)
										nb_data_pk_sent++;						
										
									//The packet was received
									if (stats_data_pk [i].time_reception != 0)
										{
											nb_data_pk_received++;
											throughput_data_pk 			+= stats_data_pk [i].pk_size;
											hops_data_pk 				+= stats_data_pk [i].hops;
											nb_retransmissions_data_pk 	+= stats_data_pk [i].nb_retry;
											delay_data_pk 				+= stats_data_pk [i].time_reception - stats_data_pk [i].time_generation;							
											(length_distribution [stats_data_pk [i].hops]) ++;
										}
									tmp_distance = sqrt( pow(stats_data_pk [i].src_x_pos - stats_data_pk [i].dest_x_pos , 2) + pow(stats_data_pk [i].src_y_pos - stats_data_pk [i].dest_y_pos , 2));
									if (DEBUG_DATA >= LOW)
										fprintf(data_file,"%d		%d		%d		%d		%d		%d		%f		%f		%f		%d		%f		%f		%s\n", stats_data_pk[i].source , stats_data_pk[i].dest , stats_data_pk[i].pk_size, stats_data_pk[i].hops , stats_data_pk[i].nb_retry , stats_data_pk[i].nb_repairs , stats_data_pk[i].time_emission , stats_data_pk[i].time_reception , stats_data_pk[i].time_reception - stats_data_pk[i].time_generation , stats_data_pk[i].method , stats_data_pk[i].time_generation , tmp_distance , stats_data_pk[i].route);
								}		
							
							tmp_distance = sqrt( pow(stats_data_pk [i].src_x_pos - stats_data_pk [i].dest_x_pos , 2) + pow(stats_data_pk [i].src_y_pos - stats_data_pk [i].dest_y_pos , 2));
							if (DEBUG_DATA>= LOW)
								fclose(data_file);
							
							//-------------------
							//	ROUTE REQUEST
							//-------------------
							if (DEBUG_ROUTE >= LOW)
								{
									sprintf(filename,"results_aodv/%d_aodv_debug_pk_rreq.txt" , begin_time_for_filenames);		
									rreq_file = fopen(filename , "w");
									fprintf(rreq_file,"SRC	|	DEST	|	SENT		|	REC		|	DELAY		|	RETRY	|	SENT		|	REC		|	HOPS	|	RETRY\n");
								}
				
							nb_rreq_sent = stats_nb_rreq;
							for (i=0 ;  i < stats_nb_rreq ; i++ )
								{
									//Nb of RREQ per route discovering
									nb_retry_for_rreq += stats_rreq [i].rreq_nb_retry;
									
									//Nb of RREQ that create a RREP
									if (stats_rreq [i].rrep_time_emission != 0)
										nb_rrep_transmitted++;							
									
							//-------------------
							//	ROUTE REPLY
							//-------------------
									if ((stats_rreq [i].rrep_time_emission != 0) && (stats_rreq[i].rrep_time_reception != 0))
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
									if (DEBUG_ROUTE >= LOW)
										fprintf(rreq_file,"%d	|	%d	|	%f	|	%f	|	%f	|	%d	|	%f	|	%f	|	%d	|	%d\n", stats_rreq[i].source , stats_rreq[i].dest , stats_rreq[i].rreq_time_emission , stats_rreq[i].rreq_time_reception , stats_rreq[i].rrep_time_reception-stats_rreq[i].rrep_time_emission , stats_rreq[i].rreq_nb_retry , stats_rreq[i].rrep_time_emission , stats_rreq[i].rrep_time_reception , stats_rreq[i].rrep_hops , stats_rreq[i].rrep_nb_retry );
								}
							if (DEBUG_ROUTE >= LOW)
								fclose(rreq_file);
							
							//-------------------
							//	ROUTE ERROR
							//-------------------
							if (DEBUG_ROUTE >= LOW)
								{
									sprintf(filename,"results_aodv/%d_aodv_debug_pk_rerr.txt" , begin_time_for_filenames);		
									rerr_file = fopen(filename , "w");
									fprintf(rerr_file,"SRC	|	DEST	|	SENT		|	REC		|	RETRY	|	HOPS\n");
								}
				
							nb_rerr_sent = stats_nb_rerr;
							for (i=0 ;  i < stats_nb_rerr ; i++ )
								{
									if (stats_rerr[i].time_reception != 0)
										{
											nb_rerr_received++;
											hops_rerr	 					+= stats_rerr [i].hops;
											average_nb_retransmissions_rrep += stats_rerr [i].nb_retry;
											average_delay_for_rerr 			+= stats_rerr [i].time_reception - stats_rerr [i].time_emission;
											nb_retry_for_rerr				+= stats_rerr [i].nb_retry;
										}
									if (DEBUG_ROUTE >= LOW)
										fprintf(rerr_file,"%d	|	%d	|	%f	|	%f	|	%d	|	%d\n" , stats_rerr[i].source , stats_rerr[i].dest , stats_rerr[i].time_emission , stats_rerr[i].time_reception , stats_rerr[i].nb_retry , stats_rerr[i].hops );
								}
							if (DEBUG_ROUTE>= LOW)
								fclose(rerr_file);
				
							
				
							
							//File Initialization	
							sprintf(filename, "results_aodv/%d_aodv_global_stats.txt" , begin_time_for_filenames);
							file = fopen (filename, "w");
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, "|                                 			Global Statistics for AODV		                                |\n");
							fprintf(file, "|                                                                                                            |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				   
					
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                           PARAMETERS                                                       |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "Nb AP									:	%d\n", 						nb_aps);
							fprintf(file, "->High Speed \n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_HIGH_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_HIGH_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_loc_high_speed_nodes);
							fprintf(file, "->Low Speed\n");
							fprintf(file, "Speed Min								:	%f\n",						SPEED_LOW_MIN);
							fprintf(file, "Speed Max								:	%f\n",						SPEED_LOW_MAX);
							fprintf(file, "Nb Nodes								:	%d\n",							nb_loc_low_speed_nodes);
							fprintf(file, "X-coordinate max							:	%f\n",						X_MAX);
							fprintf(file, "Y-coordinate max							:	%f\n",						Y_MAX);
							fprintf(file, "Duration (in seconds)						:	%f\n", 					op_sim_time());
							fprintf(file, "Number of Communicating Nodes (i.e. nb of flows)	:	%d\n", 				NB_CONNECTIONS);
							fprintf(file, "Interarrival pk time						:	%f\n", 						INTERARRIVAL_DATA_PK);
							fprintf(file, "Packet Size (in octets)						:	%d\n", 					DATA_PK_SIZE);
							fprintf(file, "Number of packet per flow					:	%d\n", 					NB_PK_PER_FLOW);
							fprintf(file, "\n\n");
				
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                              DATA                                                          |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n-------------------------------------------- TOTAL --------------------------------------------------\n");
							fprintf(file, "Nb Packets Generated						:	%d\n",  			nb_data_pk );
							fprintf(file, "Nb Packets Sent							:	%d\n",  			nb_data_pk_sent );
							fprintf(file, "Nb Packets Received						:	%d\n",  			nb_data_pk_received );
							fprintf(file, "Delivery Ratio (for generated pk)				:	%f\n", 		(double) nb_data_pk_received / (double)nb_data_pk );
							fprintf(file, "Delivery Ratio (for sent pk)					:	%f\n", 			(double) nb_data_pk_received / (double)nb_data_pk_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) delay_data_pk / (double)nb_data_pk_received );
							fprintf(file, "Average Throughput (in kbps) 					:	%f\n", 		(double) throughput_data_pk / (1024 * (op_sim_time()-TIME_BEGIN_DATA))  );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_data_pk / nb_data_pk_received  );
							fprintf(file, "Average Number of restransmissions per hop		:	%f\n",		(double) nb_retransmissions_data_pk / hops_data_pk );
							fprintf(file, "\n");
							
							fprintf(file, "\n-------------------------------------- ROUTE LENGTH DISTRIBUTION -----------------------------------------\n");
							for (i=1; i< MAX_NETWORK_RADIUS ; i++)
								if (length_distribution[i] != 0)
									fprintf(file, "%d hops								:	%d\n",		i , 	length_distribution[i]);					
							fprintf(file, "\n\n");
				
							
							
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                                           ROUTE CONTROL                                                    |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
							fprintf(file, "\n------------------------------------------- ROUTE REQUEST ---------------------------------------------------\n");
							fprintf(file, "Nb RREQ Sent							:	%d\n",  				stats_nb_rreq );
							fprintf(file, "Percentage of Successfull RREQ				:	%f\n", 			(double) nb_rrep_received / stats_nb_rreq );
							fprintf(file, "End To End Delay 1 RREQ -> 1 RREP				:	%f\n", 		(double) average_delay_for_rreq_to_final_rrep / nb_rrep_received );
							fprintf(file, "\n");
							fprintf(file, "\n--------------------------------------------- ROUTE REPLY -------------------------------------------------\n");
							fprintf(file, "Nb RREP Transmitted						:	%d\n",  			nb_rrep_transmitted );
							fprintf(file, "Nb RREP Received							:	%d\n",  			nb_rrep_received );
							fprintf(file, "Percentage of Successfull RREP (over all RREP)		:	%f\n", 	(double) nb_rrep_received / nb_rrep_transmitted );
							fprintf(file, "Percentage of Successfull RREP (over all RREQ)		:	%f\n", 	(double) nb_rrep_received / stats_nb_rreq );
							fprintf(file, "Average Delay before receiveing the RREP			:	%f\n", 		(double) average_delay_for_rrep / nb_rrep_received );
							fprintf(file, "Average Number of Retransmissions along a RREP		:	%f\n", 	(double) average_nb_retransmissions_rrep / nb_rrep_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rrep / nb_rrep_received  );
							fprintf(file, "\n");
				/*			fprintf(file, "\n--------------------------------------------- ROUTE ERROR -------------------------------------------------\n");
							fprintf(file, "Nb RERR Transmitted						:	%d\n",  			nb_rerr_sent );
							fprintf(file, "Nb RERR Received							:	%d\n",  			nb_rerr_received );
							fprintf(file, "Delivery ratio							:	%f\n", 				(double) nb_rerr_received / nb_rerr_sent );
							fprintf(file, "Average Delay (in seconds)					:	%f\n", 			(double) average_delay_for_rerr / nb_rerr_received );
							fprintf(file, "Average Number of Retransmissions per hop			:	%f\n", 	(double) average_nb_retransmissions_rerr / nb_rerr_received );
							fprintf(file, "Average route length (in hops)				:	%f\n", 			(double) hops_rerr / nb_rerr_received  );
							fprintf(file, "\n");
				*/
							fprintf(file, "\n\n");
				
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n");
							fprintf(file, "|                            NETWORK CONTROL  (in packet per second per node)                                |\n");
							fprintf(file, " ------------------------------------------------------------------------------------------------------------\n\n");
				
							nb_routing_pk_total =   ((double)  nb_routing_pk_ack_total ) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_pk_total +=  ((double) nb_routing_pk_rreq_total + nb_routing_pk_rrep_total + nb_routing_pk_rerr_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							
							fprintf(file, "--> Average packets per node per second \n");
							fprintf(file , "\n");
							fprintf(file, "Unicast Acks							:	%f\n", 			(double) nb_routing_pk_data_ack_total				/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 			(double) nb_routing_pk_data_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREQ									:	%f\n", 			(double) nb_routing_pk_rreq_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP									:	%f\n", 			(double) nb_routing_pk_rrep_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR									:	%f\n", 			(double) nb_routing_pk_rerr_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 		(double) nb_routing_pk_total);
							fprintf(file, "\n\n");
							
							nb_routing_bits_total 	=  ((double) nb_routing_bits_ack_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							nb_routing_bits_total 	+= ((double) nb_routing_bits_rreq_total + nb_routing_bits_rrep_total + nb_routing_bits_rerr_total) / ((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes);
							
							
							fprintf(file, "--> Average bits per node per second \n");
							fprintf(file , "\n");
							fprintf(file, "Unicast Acks							:	%f\n", 			(double) nb_routing_bits_data_ack_total				/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Data									:	%f\n", 			(double) nb_routing_bits_data_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREQ									:	%f\n", 			(double) nb_routing_bits_rreq_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RREP									:	%f\n", 			(double) nb_routing_bits_rrep_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "RERR									:	%f\n", 			(double) nb_routing_bits_rerr_total					/((op_sim_time()-TIME_BEGIN_DATA) * nb_nodes));
							fprintf(file, "Total									:	%f\n", 		(double) nb_routing_bits_total);
							fprintf(file, "\n\n");
							
							
							fclose(file);
						}
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (7,aodv_process)


			/** state (end) exit executives **/
			FSM_STATE_EXIT_UNFORCED (3, "end", "aodv_process () [end exit execs]")
				{
				}


			/** state (end) transition processing **/
			FSM_TRANSIT_MISSING ("end")
				/*---------------------------------------------------------*/



			/** state (mac_layer) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "mac_layer", "aodv_process () [mac_layer enter execs]")
				{
				//Ici* 		ici_ptr;
				Packet* 	pkt;
				int			pktType;
				int			pktStatId;
				int			pktPrevHop;
				int			pktIpDestAddr;
				//int			src_addr, dest_addr;
				int			pk_id;
				
				//fprintf(aodvOut, "%d: Packet from MAC layer\n", aodv_myAddr);
				
				// get incoming packet
				pkt = op_pk_get(op_intrpt_strm());
				assert(NULL != pkt);
				
				/*
				// get sender
				ici_ptr = op_intrpt_ici();
				assert(NULL != ici_ptr);
				op_ici_attr_get(ici_ptr, "src_addr", 	&src_addr);
				op_ici_attr_get(ici_ptr, "dest_addr", 	&dest_addr);
				*/
				
				// get packet type
				op_pk_nfd_get(pkt, "Type", 		&pktType);
				op_pk_nfd_get(pkt, "StatId", 	&pktStatId);
				op_pk_nfd_get(pkt, "PrevHop", 	&pktPrevHop);
				op_pk_nfd_get(pkt, "NextHop", 	&pktIpDestAddr);
				
				//dbg_print(1, "RECEIVING %i.%i from node %i\n", 
				//	pktType, pktStatId, pktPrevHop);
				
				// cancel any ack timeout (any packet received from a node is considered to be an ACK)
				aodv_ack_wait_remove(pktPrevHop, TRUE);
				
				
				if (pktIpDestAddr == aodv_myAddr || pktIpDestAddr == AODV_BROADCAST_ADDR)
					{
				
						switch (pktType) 
							{
								case PKT_TYPE_RREQ:
									{
										dbg_print(1, "RREQ received\n");
										aodv_handle_pk_rreq(pkt);
										break;
									};
						
								case PKT_TYPE_RREP:
									{
										dbg_print(1, "RREP received\n");
										aodv_handle_pk_rrep(pkt);
										break;
									};
						
								case PKT_TYPE_RERR:
									{
										dbg_print(1, "RERR received\n");
										aodv_handle_pk_rerr(pkt);
										break;
									};
						
								case PKT_TYPE_RREP_ACK:
									{
										dbg_print(1, "RREP_ACK received\n");
										aodv_handle_pk_rrep_ack(pkt);
										break;
									};
							
								case PKT_TYPE_DATA:
									{
										dbg_print(1, "DATA received\n");
										aodv_handle_pk_data(pkt);
										break;
									};
							
								default:
									{
										assert(FALSE);
									};
							}
						
					}
				else
					{
						// promiscuous mode
						dbg_print(1, "Received promiscuous packet (src %i, dest %i)\n", pktPrevHop, pktIpDestAddr);
						
						switch (pktType) 
							{		
								case PKT_TYPE_RERR:
									{
										AodvT_Address* addrListPtr = NULL;
										op_pk_nfd_get(pkt, "UnreachableDestinations", &addrListPtr);
										assert(addrListPtr);
										op_prg_mem_free(addrListPtr);
										break;
									};
							
								default:
									{
										break;
									};
							}
						
						op_pk_destroy(pkt);
					}
				
				}


			/** state (mac_layer) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "mac_layer", "aodv_process () [mac_layer exit execs]")
				{
				}


			/** state (mac_layer) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "mac_layer", "idle")
				/*---------------------------------------------------------*/



			/** state (higher_layer) enter executives **/
			FSM_STATE_ENTER_FORCED (5, state5_enter_exec, "higher_layer", "aodv_process () [higher_layer enter execs]")
				{
				Ici* ici;
				AodvT_Address destAddr;
				
				ici = op_ev_ici(op_ev_current());
				op_ici_attr_get(ici, "destAddr", &destAddr);
				assert(destAddr > 0 && destAddr <= aodv_node_count);
				
				//fprintf(aodvOut, "%d: Packet from higher layer (dest %i)\n", aodv_myAddr, destAddr);
				
				aodv_pk_data_enqueue(destAddr);
				}


			/** state (higher_layer) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "higher_layer", "aodv_process () [higher_layer exit execs]")
				{
				}


			/** state (higher_layer) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "higher_layer", "idle")
				/*---------------------------------------------------------*/



			/** state (route_discovery) enter executives **/
			FSM_STATE_ENTER_FORCED (6, state6_enter_exec, "route_discovery", "aodv_process () [route_discovery enter execs]")
				{
				
				
				AodvT_rte* rte;
				int i;
				Evhandle ev = op_ev_current();
				
				dbg_print(1, "TIMEOUT: route discovery\n");
				
				for (i = 0; i < op_prg_list_size(aodv_RT); i++)
					{
						rte = op_prg_list_access(aodv_RT, i);
						if (0 == memcmp(&ev, &rte->routeDiscoveryTimeout, sizeof(Evhandle)))
							{
								aodv_handle_timeout_route_discovery(rte);
								break;
							}
					}
				}


			/** state (route_discovery) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "route_discovery", "aodv_process () [route_discovery exit execs]")
				{
				}


			/** state (route_discovery) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "route_discovery", "idle")
				/*---------------------------------------------------------*/



			/** state (generate_pk_flow) enter executives **/
			FSM_STATE_ENTER_FORCED (7, state7_enter_exec, "generate_pk_flow", "aodv_process () [generate_pk_flow enter execs]")
				{
				
				int destAddr;
				int i;
				int network_id = 0;
				int remote_node_id = 0;
				int remote_node_process_id = 0;
				Ici* ici;
				int nextNode;
				double nextPktFlow;
				
				// choose random destination
				destAddr = op_dist_uniform(aodv_node_count-1) + 1;
				if (destAddr == aodv_myAddr)
					destAddr = (destAddr % aodv_node_count) + 1;
				if (destAddr == aodv_myAddr)
					op_sim_end("This simulation has only one node", "It is a " , "" , "");
				
				
				// create ICI
				op_ici_attr_set(aodv_flowgen_ici, "destAddr", destAddr);
				op_ici_install(aodv_flowgen_ici); // install for all events to be scheduled
				
				// schedule events for a CBR
				for (i = 0; i < NB_PK_PER_FLOW; i++)
					{
						op_intrpt_schedule_self(op_sim_time() + i*INTERARRIVAL_DATA_PK,	PKT_FROM_HIGHER_LAYER_CODE);
					}
				
				op_ici_install(OPC_NIL);
				
				dbg_print(1, "Scheduled %i data packets to be sent to node %i\n", NB_PK_PER_FLOW, destAddr);
				
				
				// get id of a remote node's routing process
				network_id 				= op_id_parent(op_id_parent(op_id_self()));
				nextNode 				= op_dist_uniform(op_topo_child_count(network_id, OPC_OBJTYPE_NDMOB)); // elect next node to be a source
				remote_node_id			= op_id_from_sysid(OPC_OBJTYPE_NDMOB, nextNode);
				remote_node_process_id	= op_id_from_name(remote_node_id, OPC_OBJMTYPE_QPS, AODV_ROUTING_PROCESS_NAME);
				
				// schedule next packet flow
				nextPktFlow = op_sim_time() + op_dist_exponential(NB_PK_PER_FLOW * INTERARRIVAL_DATA_PK);
				op_intrpt_schedule_remote(nextPktFlow, GENERATE_PKT_FLOW_CODE, remote_node_process_id);
				
				dbg_print(1, "Scheduled next data flow at %1.8f, source node %i\n", nextPktFlow, nextNode);
				}


			/** state (generate_pk_flow) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "generate_pk_flow", "aodv_process () [generate_pk_flow exit execs]")
				{
				}


			/** state (generate_pk_flow) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "generate_pk_flow", "idle")
				/*---------------------------------------------------------*/



			/** state (mac_ack) enter executives **/
			FSM_STATE_ENTER_FORCED (8, state8_enter_exec, "mac_ack", "aodv_process () [mac_ack enter execs]")
				{
				Ici* ici;
				AodvT_Address addr;
				
				ici = op_intrpt_ici();
				assert(ici != NULL);
				
				op_ici_attr_get(ici, "destination_addr", &addr);
				
				dbg_print(1, "ACK_FROM_MAC_LAYER for node %i\n", addr);
				
				aodv_ack_wait_remove(addr, TRUE);
				
				op_ici_destroy(ici);
				}


			/** state (mac_ack) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "mac_ack", "aodv_process () [mac_ack exit execs]")
				{
				}


			/** state (mac_ack) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "mac_ack", "idle")
				/*---------------------------------------------------------*/



			/** state (ack_timeout) enter executives **/
			FSM_STATE_ENTER_FORCED (9, state9_enter_exec, "ack_timeout", "aodv_process () [ack_timeout enter execs]")
				{
				/*	6.10
					If layer-2 notification is not available, passive acknowledgment
				    SHOULD be used when the next hop is expected to forward the
				    packet, by listening to the channel for a transmission attempt
				    made by the next hop.  If transmission is not detected within
				    NEXT_HOP_WAIT milliseconds or the next hop is the destination (and
				    thus is not supposed to forward the packet) one of the following
				    methods SHOULD be used to determine connectivity:
				
				    *  Receiving any packet (including a Hello message) from the next
				       hop.
				
				    *  A RREQ unicast to the next hop, asking for a route to the next
				       hop.
				
					*  An ICMP Echo Request message unicast to the next hop.
				
				    If a link to the next hop cannot be detected by any of these methods,
				    the forwarding node SHOULD assume that the link is lost, and take
				    corrective action by following the methods specified in Section 6.11.
				*/
				
				
				AodvT_ack_wait_entry* awe;
				AodvT_rte* rte;
				int i;
				Evhandle ev;
				
				
				ev = op_ev_current();
				
				for (i = 0; i < op_prg_list_size(aodv_ack_wait); i++)
					{
						awe = op_prg_list_access(aodv_ack_wait, i);
						if (0 == memcmp(&ev, &awe->timeout, sizeof(Evhandle)))
							{
								break;
							}
					}
				assert(awe != NULL);
				
				rte = aodv_rte_get(awe->destAddr);
				assert(rte != NULL);
				assert(!rte->acknowledged);
				
				if (!awe->pinged)
					{
						int aodv_ttl_value = 1;
								
						//dbg_print(1, "Ack timeout for node %i\n", awe->destAddr);
						//printf("Ack timeout for node %i\n", awe->destAddr);
						
						// unicasting RREQ to the node
						aodv_pk_send_rreq_to_addr(awe->destAddr, 1, awe->destAddr);
				
						awe->pinged = TRUE;
						awe->timeout = op_intrpt_schedule_self(op_sim_time() + AODV_RING_TRAVERSAL_TIME, TIMEOUT_ACK_CODE);
					}
				else
					{
						//dbg_print(2, "Link breakage to node %i detected\n", awe->destAddr);
						//printf("Link breakage to node %i detected\n", awe->destAddr);
						
						aodv_rte_invalidate_route(rte);
						
						if (op_prg_list_size(rte->precursors) > 0)
							aodv_pk_send_rerr(awe->destAddr);
						
						aodv_ack_wait_remove(awe->destAddr, FALSE);
						
						// if we have still have data queued, re-request a route
						if (op_prg_list_size(rte->queuedPackets) > 0 && !rte->routeDiscovery)
							{
								aodv_initiate_rreq(rte, rte->hopCount + AODV_TTL_INCREMENT);
							}
					}
				
				}


			/** state (ack_timeout) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "ack_timeout", "aodv_process () [ack_timeout exit execs]")
				{
				}


			/** state (ack_timeout) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "ack_timeout", "idle")
				/*---------------------------------------------------------*/



			/** state (send_hello) enter executives **/
			FSM_STATE_ENTER_FORCED (10, state10_enter_exec, "send_hello", "aodv_process () [send_hello enter execs]")
				{
				
				
				if (aodv_config_hellos)
					{
						if (!bc_during_hello_interval)
							{	
								BOOL activeRoute = FALSE;
								
								if (op_prg_list_size(aodv_RT) > 0)
									{
										AodvT_rte* rte;
										int i;
										
										for (i = 0; i < op_prg_list_size(aodv_RT); i++)
											{
												rte = op_prg_list_access(aodv_RT, i);
												activeRoute = rte->routeValid;
												if (activeRoute)
													break; // for
											}
									}
								
								if (activeRoute)
									aodv_pk_send_hello();
							}
						
						bc_during_hello_interval = FALSE;
						op_intrpt_schedule_self(op_sim_time() + AODV_HELLO_INTERVAL, SEND_HELLO_CODE);
					}
				}


			/** state (send_hello) exit executives **/
			FSM_STATE_EXIT_FORCED (10, "send_hello", "aodv_process () [send_hello exit execs]")
				{
				}


			/** state (send_hello) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_hello", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (2,aodv_process)
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
aodv_process_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (aodv_process_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (aodv_process)",
			sizeof (aodv_process_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((aodv_process_state *)(*gen_state_pptr))->current_block = 4;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
aodv_process_diag (void)
	{
	/* No Diagnostic Block */
	}




void
aodv_process_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (aodv_process_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in aodv_process_svar function. */
#undef aodv_myAddr
#undef aodv_myInfo
#undef aodv_RT
#undef aodv_RREQs
#undef aodv_stats
#undef aodv_ack_wait
#undef aodv_config_wlan_ack
#undef aodv_config_wlan_promiscuous_mode
#undef aodv_config_passive_ack
#undef aodv_config_hellos
#undef aodv_flowgen_ici
#undef bc_during_hello_interval
#undef my_stat_id
#undef is_AP
#undef ack_table
#undef DATA_PK_SIZE
#undef INTERARRIVAL_DATA_PK
#undef NB_PK_PER_FLOW
#undef NB_CONNECTIONS
#undef ici_list



void
aodv_process_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	aodv_process_state		*prs_ptr;

	FIN (aodv_process_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (aodv_process_state *)gen_ptr;

	if (strcmp ("aodv_myAddr" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_myAddr);
		FOUT;
		}
	if (strcmp ("aodv_myInfo" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_myInfo);
		FOUT;
		}
	if (strcmp ("aodv_RT" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_RT);
		FOUT;
		}
	if (strcmp ("aodv_RREQs" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_RREQs);
		FOUT;
		}
	if (strcmp ("aodv_stats" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_stats);
		FOUT;
		}
	if (strcmp ("aodv_ack_wait" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_ack_wait);
		FOUT;
		}
	if (strcmp ("aodv_config_wlan_ack" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_config_wlan_ack);
		FOUT;
		}
	if (strcmp ("aodv_config_wlan_promiscuous_mode" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_config_wlan_promiscuous_mode);
		FOUT;
		}
	if (strcmp ("aodv_config_passive_ack" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_config_passive_ack);
		FOUT;
		}
	if (strcmp ("aodv_config_hellos" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_config_hellos);
		FOUT;
		}
	if (strcmp ("aodv_flowgen_ici" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->aodv_flowgen_ici);
		FOUT;
		}
	if (strcmp ("bc_during_hello_interval" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->bc_during_hello_interval);
		FOUT;
		}
	if (strcmp ("my_stat_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_stat_id);
		FOUT;
		}
	if (strcmp ("is_AP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->is_AP);
		FOUT;
		}
	if (strcmp ("ack_table" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ack_table);
		FOUT;
		}
	if (strcmp ("DATA_PK_SIZE" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->DATA_PK_SIZE);
		FOUT;
		}
	if (strcmp ("INTERARRIVAL_DATA_PK" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->INTERARRIVAL_DATA_PK);
		FOUT;
		}
	if (strcmp ("NB_PK_PER_FLOW" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_PK_PER_FLOW);
		FOUT;
		}
	if (strcmp ("NB_CONNECTIONS" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->NB_CONNECTIONS);
		FOUT;
		}
	if (strcmp ("ici_list" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->ici_list);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

