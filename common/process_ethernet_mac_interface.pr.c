/* Process model C form file: process_ethernet_mac_interface.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char process_ethernet_mac_interface_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 41BD5F87 41BD5F87 1 ares-theo-1 Fabrice@Theoleyre 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                        ";
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

/* Include the required external files  */
#include "oms_pr.h"
#include "oms_tan.h"
#include "oms_auto_addr_support.h"

/* Defines the default maximum and minimum values  */
/* for the  destination address                    */
#define MAX_DEST_ADDR			-2
#define MIN_DEST_ADDR			-2

/* Define maximum number of attempts to	*/
/* find a destination address.			*/
#define	TRY_THRESH				1024

/* Define the value for Broadcast	*/
#define BROADCAST		-1

/* Definition for the transition conditions  */
#define MAC_LAYER_PKT_ARRVL  (intrpt_type == OPC_INTRPT_STRM && intrpt_strm == instrm_from_mac)
#define APPL_LAYER_PKT_ARRVL (intrpt_type == OPC_INTRPT_STRM && intrpt_strm != instrm_from_mac)

/* Definitions of the local functions for this process  */
static void		eth_mac_higher_layer_intf_init ();
static void     eth_gen_error(const char* msg0, const char* msg1, const char* msg2);
static void		eth_gen_warn (const char *msg0, const char *msg1, const char *msg2);

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
	Objid	                  		my_id;
	Objid	                  		own_node_objid;
	Objid	                  		subnet_objid;
	Prohandle	              		own_prohandle;
	char	                   		proc_model_name[20];
	OmsT_Pr_Handle	         		own_process_record_handle;
	int	                    		outstrm_to_mac;
	int	                    		instrm_from_mac;
	Ici*	                   		intf_mac_req_iciptr;
	Packet *	               		pkptr;
	int	                    		destination_address;
	int	                    		low_dest_index;
	int	                    		high_dest_index;
	OmsT_Aa_Address_Handle	 		oms_aa_handle;
	int	                    		mac_address;
	} process_ethernet_mac_interface_state;

#define pr_state_ptr            		((process_ethernet_mac_interface_state*) SimI_Mod_State_Ptr)
#define my_id                   		pr_state_ptr->my_id
#define own_node_objid          		pr_state_ptr->own_node_objid
#define subnet_objid            		pr_state_ptr->subnet_objid
#define own_prohandle           		pr_state_ptr->own_prohandle
#define proc_model_name         		pr_state_ptr->proc_model_name
#define own_process_record_handle		pr_state_ptr->own_process_record_handle
#define outstrm_to_mac          		pr_state_ptr->outstrm_to_mac
#define instrm_from_mac         		pr_state_ptr->instrm_from_mac
#define intf_mac_req_iciptr     		pr_state_ptr->intf_mac_req_iciptr
#define pkptr                   		pr_state_ptr->pkptr
#define destination_address     		pr_state_ptr->destination_address
#define low_dest_index          		pr_state_ptr->low_dest_index
#define high_dest_index         		pr_state_ptr->high_dest_index
#define oms_aa_handle           		pr_state_ptr->oms_aa_handle
#define mac_address             		pr_state_ptr->mac_address

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	process_ethernet_mac_interface_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
static void  
eth_mac_higher_layer_intf_init ()
    {  
    /** Initializes the state variables for this process model  **/
    /** and registers itself in the model-wide reigtry          **/
    FIN (eth_mac_higher_layer_intf_init ());

    /* Gets its own id  */     
    my_id = op_id_self  ();
   
    /* Gets the object id of the node to which this module belongs  */
    own_node_objid 	=   op_topo_parent (my_id);
  
    /* Gets the objid of its subnet  */
    subnet_objid 	=   op_topo_parent (own_node_objid);
    
    /* Gets a handle to its process  */
    own_prohandle	=   op_pro_self ();

    /* Gets the name of its process model  */
    op_ima_obj_attr_get (my_id, "process model", proc_model_name);
  
    /* Gets a process record handle to record its process in  */
    /* the regisrty                                           */
    own_process_record_handle = (OmsT_Pr_Handle) oms_pr_process_register (own_node_objid, my_id, 
                                 own_prohandle, proc_model_name);
  
    /* Sets the required attributes in the process registry  */
    oms_pr_attr_set (own_process_record_handle, 
	    			"location", 	OMSC_PR_STRING, 	"mac_if",
		    		"subnet", 		OMSC_PR_OBJID, 		subnet_objid, 
			    	OPC_NIL);

    /* Stream numbers to the mac layer and from the mac layer which  */
    /* which will be set in the exit execs of the wait state         */ 
    outstrm_to_mac  = OPC_INT_UNDEF; 
	instrm_from_mac = OPC_INT_UNDEF;

    FOUT;
    } 

static void
eth_mac_higher_layer_intf_error (const char* msg0, const char* msg1, const char* msg2)
	{
	/** Print an error message and exit the simulation. **/
	FIN (eth_mac_higher_layer_intf_error (msg0, msg1, msg2));
	
	op_sim_end ("Error in Ethernet MAC Interface model (ethernet_mac_interface):",
		msg0, msg1, msg2);
	
	FOUT;
	}

static void
eth_mac_higher_layer_intf_warn (const char *msg0, const char *msg1, const char *msg2)
	{
	/** Print a warning message and resume. **/
	FIN (eth_mac_higher_layer_intf_warn (msg0, msg1, msg2));
	
	op_prg_odb_print_major ("Warning from Ethernet interface model (eth_mac_interface):",
		msg0, msg1, msg2, OPC_NIL);
	
	FOUT;
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
	void process_ethernet_mac_interface (void);
	Compcode process_ethernet_mac_interface_init (void **);
	void process_ethernet_mac_interface_diag (void);
	void process_ethernet_mac_interface_terminate (void);
	void process_ethernet_mac_interface_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
process_ethernet_mac_interface (void)
	{
	int _block_origin = 0;
	FIN (process_ethernet_mac_interface ());
	if (1)
		{
		List*           	proc_record_handle_list_ptr;
		int             	record_handle_list_size;
		OmsT_Pr_Handle  	process_record_handle;
		Objid           	mac_module_objid;
		int             	intrpt_type = OPC_INT_UNDEF;
		int             	intrpt_strm = OPC_INT_UNDEF;
		double				ne_address = OPC_DBL_UNDEF;
		int		        	curr_dest_addr = OMSC_AA_AUTO_ASSIGN;
		int					low_dest_addr;
		int					high_dest_addr;
		char				err_msg [128];
		int					num_tries;


		FSM_ENTER (process_ethernet_mac_interface)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "init", "process_ethernet_mac_interface () [init enter execs]")
				{
				/* This function initializes its state variables and  */
				/* registers itself in the process registry           */ 
				eth_mac_higher_layer_intf_init ();
				
				/* Set up an interface control information (ICI) structure to	*/
				/* communicate parameters to the MAC layer process.  We will	*/
				/* leave this ICI installed for the entire simulation.			*/
				intf_mac_req_iciptr = op_ici_create ("mac_request");
				op_ici_install (intf_mac_req_iciptr);
				
				/* Schedules a self interrrupt  */
				op_intrpt_schedule_self (op_sim_time (), 0);
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,process_ethernet_mac_interface)


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "init", "process_ethernet_mac_interface () [init exit execs]")
				{
				}


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (5, state5_enter_exec, ;, "default", "", "init", "init2")
				/*---------------------------------------------------------*/



			/** state (wait) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, state1_enter_exec, "wait", "process_ethernet_mac_interface () [wait enter execs]")
				{
				/* Schedule a self interrupt to wait for lower layer	*/
				/* Ethernet MAC process to initialize and register      */
				/* itself in the model-wide process registry.			*/
				op_intrpt_schedule_self (op_sim_time (), 0);
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,process_ethernet_mac_interface)


			/** state (wait) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "wait", "process_ethernet_mac_interface () [wait exit execs]")
				{
				/* Obtain the MAC layer information for the local MAC	*/
				/* process from the model-wide registry.				*/
				proc_record_handle_list_ptr = op_prg_list_create ();
				oms_pr_process_discover (my_id, proc_record_handle_list_ptr,
					"node objid",   OMSC_PR_OBJID,      own_node_objid,  
				 	"protocol", 	OMSC_PR_STRING,		"mac",
					OPC_NIL);
				
				/* If the MAC process registered itself, then there	*/
				/* must be a valid match							*/
				record_handle_list_size = op_prg_list_size (proc_record_handle_list_ptr);
				if (record_handle_list_size != 1)
					{
					/* An error should be created if there are more	    */
					/* than one Ethernet-MAC process in the local node,	*/
					/* or if no match is found.						    */
					op_sim_end ("Error: either zero or several Ethernet MAC processes found in the interface", "", "", "");
					}
				else
					{
					/*	Obtain a handle on the process record.	*/
					process_record_handle = (OmsT_Pr_Handle) op_prg_list_access (proc_record_handle_list_ptr, OPC_LISTPOS_HEAD);
				
					/* Obtain the module objid for the Ethernet MAC module. 		*/
					oms_pr_attr_get (process_record_handle, "module objid", OMSC_PR_OBJID, &mac_module_objid); 
				
					/* Obtain the address handle maintained by the MAC process.	*/
					oms_pr_attr_get (process_record_handle, "address",             OMSC_PR_NUMBER,  &ne_address);
					oms_pr_attr_get (process_record_handle, "auto address handle", OMSC_PR_ADDRESS, &oms_aa_handle);
				
					/* Set the variable to indicate the MAC address of the	*/
					/* associated MAC layer process.						*/
					mac_address = (int) ne_address; 
				
					/* Obtain the stream numbers connected to and from the	    */
					/* Ethernet MAC layer process.								*/
					oms_tan_neighbor_streams_find (my_id, mac_module_objid, &instrm_from_mac, &outstrm_to_mac);
					}
				
				if (oms_aa_handle == OPC_NIL)
					{
					/* This is a unconnected node. Do nothing */
					}
				else
					{
					/* Determine address range for destination assignment. */
					if ((op_ima_obj_attr_get (my_id, "low dest address", &low_dest_addr)   == OPC_COMPCODE_FAILURE) ||
						(op_ima_obj_attr_get (my_id, "high dest address", &high_dest_addr) == OPC_COMPCODE_FAILURE))
						{
						eth_mac_higher_layer_intf_error ("Unable to read destination address range.", OPC_NIL, OPC_NIL);
						}
				
					/* If any single address is specified as broadcast, indicate this as an error */
					/* Both the low and high destination addresses together can be specified as broadcast */
					if (((low_dest_addr == -1) && (high_dest_addr != -1)) || 
						((high_dest_addr == -1) && (low_dest_addr != -1)))
						{
						eth_mac_higher_layer_intf_error ("Both the Lowest and Highest Destination addresses must be specified as Broadcast", "Any one attribute cannot be Broadcast", OPC_NIL);
						}
				
					/* Check whether highest destination address is not lower than the lowest destination 		*/
					/* address (also check it is not a broadcast address or MAX_DEST_ADDR).						*/
					if ((high_dest_addr < low_dest_addr) && (high_dest_addr >= 0))
						{
						eth_mac_higher_layer_intf_warn ("Specified lowest destination address is greater than specified highest destination address.",
							"Setting the lowest destination address to Minimum Dest Address, and the highest to Maximum Dest Address.", OPC_NIL);
				
						/* If so, then set the lowest destination address to the minimum destination address	*/
						/* and the highest destination address to the highest destination address.  			*/
						low_dest_addr  = MIN_DEST_ADDR;
						high_dest_addr = MAX_DEST_ADDR;    
						}
				
					/* Determine our destination or destination range. Start by initializing the	*/
					/* range indices, which are used if a range is specified.						*/
					low_dest_index  = OMSC_AA_UNINIT_ADDR;
					high_dest_index = OMSC_AA_UNINIT_ADDR;
					if ((low_dest_addr == MIN_DEST_ADDR) && (high_dest_addr == MAX_DEST_ADDR))
						{
						/* We randomly pick our destination from universal address set.				*/
						destination_address = OMSC_AA_AUTO_ASSIGN;
						}
					else if (low_dest_addr == high_dest_addr)
						{
						/* We have a unique destination address specified. Check its validity.		*/
						if (low_dest_addr == -1)
							destination_address = OMSC_AA_BROADCAST;
						else if (oms_aa_dest_addr_check (oms_aa_handle, low_dest_addr) == OPC_TRUE)
							destination_address = low_dest_addr;
						else
							{
							sprintf (err_msg,  "%d", low_dest_addr); 
							eth_mac_higher_layer_intf_error ("Invalid destination MAC address.", "No MAC was found with the address:",err_msg);
							}
						}
					else
						{
						/* We randomly pick our destination addresses from a subset of the			*/
						/* universal address set. Determine the lower and upper indices of this		*/
						/* subset in the global address array.										*/
						if (low_dest_addr == MIN_DEST_ADDR)
							low_dest_index = 0;
						else
							{
							low_dest_index = oms_aa_address_find (oms_aa_handle, low_dest_addr);
				
							/* Check validity of the lower bound.									*/
							if (low_dest_index < 0)
								{
								sprintf (err_msg, "%d", low_dest_addr); 
								eth_mac_higher_layer_intf_error ("Invalid destination MAC address.", "No MAC was found with the address:", err_msg);
								}
							else if (oms_aa_dest_addr_check (oms_aa_handle, low_dest_addr) == OPC_FALSE)
								{
								sprintf (err_msg, "MAC address specified as the lowest destination address (%d)", low_dest_addr); 
								eth_mac_higher_layer_intf_error (err_msg, "is not configured as a valid destination address.", 
										"Most probably that MAC belongs to a switch or bridge node.");
								}
							}
				
						/* Now determine the upper bound.											*/
						if (high_dest_addr == MAX_DEST_ADDR)
							high_dest_index = oms_aa_max_addr_index_get (oms_aa_handle);
						else
							{
							high_dest_index = oms_aa_address_find (oms_aa_handle, high_dest_addr);
				
							/* Check validity of the upper bound.									*/
							if (high_dest_index < 0)
								{
								sprintf (err_msg, "%d", high_dest_addr); 
								eth_mac_higher_layer_intf_error ("Invalid destination MAC address.", "No MAC was found with the address:", err_msg);
								}
							else if (oms_aa_dest_addr_check (oms_aa_handle, high_dest_addr) == OPC_FALSE)
								{
								sprintf (err_msg, "MAC address specified as the highest destination address (%d)", high_dest_addr); 
								eth_mac_higher_layer_intf_error (err_msg, "is not configured as a valid destination address.", 
											"Most probably that MAC belongs to a switch or bridge node.");
								}
							}
						}
					}
				}


			/** state (wait) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "wait", "idle")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, state2_enter_exec, "idle", "process_ethernet_mac_interface () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,process_ethernet_mac_interface)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "idle", "process_ethernet_mac_interface () [idle exit execs]")
				{
				/* The only interrupt expected in this state is a	*/
				/* stream interrupt. It can be either from the MAC	*/
				/* layer for a packet destined for this node or		*/
				/* from the application layer for a packet destined	*/
				/* for some other node.								*/
				intrpt_type = op_intrpt_type ();
				intrpt_strm = op_intrpt_strm ();
				
				/*Get the packet from the appropriate stream        */
				pkptr = op_pk_get (intrpt_strm);
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (APPL_LAYER_PKT_ARRVL)
			FSM_TEST_COND (MAC_LAYER_PKT_ARRVL)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 3, state3_enter_exec, ;, "APPL_LAYER_PKT_ARRVL", "", "idle", "appl layer arrival")
				FSM_CASE_TRANSIT (1, 4, state4_enter_exec, ;, "MAC_LAYER_PKT_ARRVL", "", "idle", "mac layer arrival")
				}
				/*---------------------------------------------------------*/



			/** state (appl layer arrival) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "appl layer arrival", "process_ethernet_mac_interface () [appl layer arrival enter execs]")
				{
				/* A packet has arrived from the application layer.	Pick a random		*/
				/* destination, unless an explicit destination is specified. Don't try	*/
				/* infinite times.													*/
				num_tries = 0;
				
				/* A packet arrived from the MAC layer. Since the MAC	*/
				/* layer would have forwarded this only if it were		*/
				/* destined for this node, forward this packet to the	*/
				/* application layer.									*/
				
				do	
					{
					/* Increment the try counter.  This will prevent an infinite loop.	*/
					num_tries++;
				
					/* Pick a random destination address unless the destination address	*/
					/* is already set to a specific value.								*/
					if (low_dest_index + high_dest_index > 0)
						oms_aa_dest_addr_from_range_get (oms_aa_handle, &curr_dest_addr, low_dest_index, high_dest_index);
					else
						{
						curr_dest_addr = destination_address;
						oms_aa_dest_addr_get (oms_aa_handle, &curr_dest_addr);
						}
					} while ((curr_dest_addr == mac_address) && (num_tries < TRY_THRESH));
				
				
				if (curr_dest_addr == mac_address)
					eth_mac_higher_layer_intf_error ("Unable to choose remote address.", OPC_NIL, OPC_NIL);
				
				//Sent in broadcast
				curr_dest_addr = BROADCAST;
				
				if (curr_dest_addr == OMSC_AA_UNINIT_ADDR)
					{
					op_pk_destroy (pkptr);
					}
				else
					{
					/* Set this information in the interface control	*/
					/* information to be sent to the MAC layer.			*/
					op_ici_attr_set (intf_mac_req_iciptr, "dest_addr", curr_dest_addr);
				
					/* Send the packet to the lower layer */
					op_pk_send (op_pk_copy(pkptr), outstrm_to_mac);
					if (curr_dest_addr == BROADCAST)
						op_pk_send (pkptr, 0);
					}
				}


			/** state (appl layer arrival) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "appl layer arrival", "process_ethernet_mac_interface () [appl layer arrival exit execs]")
				{
				}


			/** state (appl layer arrival) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "appl layer arrival", "idle")
				/*---------------------------------------------------------*/



			/** state (mac layer arrival) enter executives **/
			FSM_STATE_ENTER_FORCED (4, state4_enter_exec, "mac layer arrival", "process_ethernet_mac_interface () [mac layer arrival enter execs]")
				{
				/* A packet arrived from the MAC layer. Since the MAC	*/
				/* layer would have forwarded this only if it were		*/
				/* destined for this node, forward this packet to the	*/
				/* application layer.									*/
				op_pk_send (pkptr, 0);
				}


			/** state (mac layer arrival) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "mac layer arrival", "process_ethernet_mac_interface () [mac layer arrival exit execs]")
				{
				}


			/** state (mac layer arrival) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "mac layer arrival", "idle")
				/*---------------------------------------------------------*/



			/** state (init2) enter executives **/
			FSM_STATE_ENTER_UNFORCED (5, state5_enter_exec, "init2", "process_ethernet_mac_interface () [init2 enter execs]")
				{
				/* Schedule a self interrupt to wait for lower layer	*/
				/* Ethernet MAC process to initialize and register      */
				/* itself in the model-wide process registry.			*/
				op_intrpt_schedule_self (op_sim_time (), 0);
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (11,process_ethernet_mac_interface)


			/** state (init2) exit executives **/
			FSM_STATE_EXIT_UNFORCED (5, "init2", "process_ethernet_mac_interface () [init2 exit execs]")
				{
				}


			/** state (init2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init2", "wait")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,process_ethernet_mac_interface)
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
process_ethernet_mac_interface_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (process_ethernet_mac_interface_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (process_ethernet_mac_interface)",
			sizeof (process_ethernet_mac_interface_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
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
		((process_ethernet_mac_interface_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
process_ethernet_mac_interface_diag (void)
	{
	/* No Diagnostic Block */
	}




void
process_ethernet_mac_interface_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (process_ethernet_mac_interface_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in process_ethernet_mac_interface_svar function. */
#undef my_id
#undef own_node_objid
#undef subnet_objid
#undef own_prohandle
#undef proc_model_name
#undef own_process_record_handle
#undef outstrm_to_mac
#undef instrm_from_mac
#undef intf_mac_req_iciptr
#undef pkptr
#undef destination_address
#undef low_dest_index
#undef high_dest_index
#undef oms_aa_handle
#undef mac_address



void
process_ethernet_mac_interface_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	process_ethernet_mac_interface_state		*prs_ptr;

	FIN (process_ethernet_mac_interface_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (process_ethernet_mac_interface_state *)gen_ptr;

	if (strcmp ("my_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_id);
		FOUT;
		}
	if (strcmp ("own_node_objid" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->own_node_objid);
		FOUT;
		}
	if (strcmp ("subnet_objid" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->subnet_objid);
		FOUT;
		}
	if (strcmp ("own_prohandle" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->own_prohandle);
		FOUT;
		}
	if (strcmp ("proc_model_name" , var_name) == 0)
		{
		*var_p_ptr = (char *) (prs_ptr->proc_model_name);
		FOUT;
		}
	if (strcmp ("own_process_record_handle" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->own_process_record_handle);
		FOUT;
		}
	if (strcmp ("outstrm_to_mac" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->outstrm_to_mac);
		FOUT;
		}
	if (strcmp ("instrm_from_mac" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->instrm_from_mac);
		FOUT;
		}
	if (strcmp ("intf_mac_req_iciptr" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->intf_mac_req_iciptr);
		FOUT;
		}
	if (strcmp ("pkptr" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->pkptr);
		FOUT;
		}
	if (strcmp ("destination_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->destination_address);
		FOUT;
		}
	if (strcmp ("low_dest_index" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->low_dest_index);
		FOUT;
		}
	if (strcmp ("high_dest_index" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->high_dest_index);
		FOUT;
		}
	if (strcmp ("oms_aa_handle" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->oms_aa_handle);
		FOUT;
		}
	if (strcmp ("mac_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mac_address);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

