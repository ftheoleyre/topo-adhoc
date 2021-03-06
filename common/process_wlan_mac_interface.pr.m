MIL_3_Tfile_Hdr_ 81A 70A modeler 9 4076516C 41E5501E 21 ares-theo-1 Fabrice@Theoleyre 0 0 none none 0 0 none 36AC8D3D 3CCC 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                              ��g�      <  V  Z  K  �  �  8?  8C  8�  8�  8�  :�  :�      Type of Service    �������    ����   0          Best Effort (0)          ����         ����         Best Effort (0)       ����      Background (1)      ����      Standard (2)      ����      Excellent Effort (3)      ����      Streaming Multimedia (4)      ����      Interactive Multimedia (5)      ����      Interactive Voice (6)      ����      Reserved (7)      ����         Indicates packet's type of    service (TOS). SRP MAC uses    this to determine the    priority of the packet.       
   begsim intrpt         
   ����   
   doc file            	nd_module      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����            begsim intrpt      begsim intrpt����   ����           ����          ����          ����                        3/* Object identifier of the surrounding module.	 */   Objid	\my_objid;       1/* Object identifier of the surrounding node.	 */   Objid	\my_node_objid;       8/* Stream index of the packet stream coming from MAC. */   int	\instrm_from_mac;       5/* Stream index of the packet stream going to MAC. */   int	\outstrm_to_mac;       5/* Auto-address assignment handle. Used while      */   5/* auto-address and destination address selection. */   &OmsT_Aa_Address_Handle	\oms_aa_handle;       ,/* Element address of the associated MAC. */   int	\mac_address;       6/* Interface control information needed to indicate */   6/* to the MAC of the destination to which packet    */   6/* needs to be sent.                                */   Ici*	\wlan_mac_req_iciptr;          %List*				proc_record_handle_list_ptr;    int					record_handle_list_size;   &OmsT_Pr_Handle		process_record_handle;   Objid				mac_module_objid;   &Boolean				dest_addr_okay = OPC_FALSE;   %double				ne_address = OPC_DBL_UNDEF;   -int					curr_dest_addr = OMSC_AA_AUTO_ASSIGN;   Packet*				pkptr;   $int					intrpt_type = OPC_INT_UNDEF;   $int					intrpt_strm = OPC_INT_UNDEF;   
int					i;   ,OmsT_Aa_Address_Info * ith_address_info_ptr;           Ici*	ici_dest_ptr;      /***** Include Files. *****/       %/* Address assignment definitions.	*/   "#include "oms_auto_addr_support.h"       ,/* Topology analysis-related definitions. */   #include "oms_tan.h"       +/* Process registry-related definitions. */   #include "oms_pr.h"        /***** Transition Macros ******/   ]#define MAC_LAYER_PKT_ARVL	(intrpt_type == OPC_INTRPT_STRM && intrpt_strm == instrm_from_mac)   ^#define APPL_LAYER_PKT_ARVL	(intrpt_type == OPC_INTRPT_STRM && intrpt_strm != instrm_from_mac)   #define MAC_BROADCAST		-1       %/***** Functional declaration ******/   4static void			wlan_mac_higher_layer_intf_sv_init ();   7static void			wlan_mac_higher_layer_register_as_arp ();       <   static void   %wlan_mac_higher_layer_intf_sv_init ()   	{   	int			type_of_service;       5	/** Initializes all state variables used in this	**/   	/** process model.									**/   -	FIN (wlan_mac_higher_layer_intf_sv_init ());       =	/* Object identifier for the surrounding module and node.	*/   	my_objid = op_id_self ();   +	my_node_objid = op_topo_parent (my_objid);       7	/* Stream indices to and from the WLAN MAC process.	*/   7	/* these will be set in the "exit execs" of "init".	*/   !	outstrm_to_mac  = OPC_INT_UNDEF;   !	instrm_from_mac = OPC_INT_UNDEF;       7	/* Determine the destination to which packet should	*/   7	/* be sent,and the prioritization to be provided to	*/   $	/* the transmitted packet.							*/   H	op_ima_obj_attr_get (my_objid, "Type of Service", 	  &type_of_service);       6	/* Some interface control information is needed to	*/   6	/* indicate to the MAC of the destination to which	*/   3	/* a given packet needs to be sent. Create it.		*/   :	wlan_mac_req_iciptr = op_ici_create ("wlan_mac_request");   K	op_ici_attr_set (wlan_mac_req_iciptr, "type_of_service", type_of_service);   A	op_ici_attr_set (wlan_mac_req_iciptr, "protocol_type",   0x800);       	FOUT;   	}       static void   (wlan_mac_higher_layer_register_as_arp ()   	{   	char				proc_model_name [128];   +	OmsT_Pr_Handle		own_process_record_handle;   	Prohandle			own_prohandle;       B	/** Register this process in the model-wide process registry.	**/   0	FIN (wlan_mac_higher_layer_register_as_arp ());       8	/* Obtain the process model name and process handle.	*/   B	op_ima_obj_attr_get (my_objid, "process model", proc_model_name);    	own_prohandle = op_pro_self ();       ?	/* Register this process in the model-wide process registry	*/   G	own_process_record_handle = (OmsT_Pr_Handle) oms_pr_process_register (   <			my_node_objid, my_objid, own_prohandle, proc_model_name);       ?	/* Register this protocol attribute and the element address	*/   6	/* of this process into the model-wide registry.			*/   ,	oms_pr_attr_set (own_process_record_handle,   &		"protocol",		OMSC_PR_STRING,		"arp",   		OPC_NIL);       	FOUT;   	}                  
   Z   �          
   init   
       
      8/* Initialize the state variables used by this model.	*/   &wlan_mac_higher_layer_intf_sv_init ();       8/* Register this process as "arp" so that lower layer	*/   )/* MAC process can connect to it.						*/   )wlan_mac_higher_layer_register_as_arp ();       7/* Schedule a self interrupt to wait for lower layer	*/   ;/* wlan MAC process to initialize and register itself in	*/   +/* the model-wide process registry.						*/   ,op_intrpt_schedule_self (op_sim_time (), 0);       
       
      7/* Schedule a self interrupt to wait for lower layer	*/   :/* wlan MAC process to initialize and register itself in*/   +/* the model-wide process registry.						*/   ,op_intrpt_schedule_self (op_sim_time (), 0);       
           ����             pr_state        �   �          
   idle   
       
          
       
   	   4/* The only interrupt expected in this state is a	*/   5/* stream interrupt. It can be either from the MAC	*/   3/* layer for a packet destined for this node or		*/   6/* from the application layer for a packet destined	*/   !/* for some other node.								*/    intrpt_type = op_intrpt_type ();    intrpt_strm = op_intrpt_strm ();    pkptr = op_pk_get (intrpt_strm);       
           ����             pr_state        :   Z          
   appl layer arrival   
    @  
   6   6/* A packet has arrived from the application layer.	*/   6/* If the destination address specified is "Random"	*/   6/* then generate a destination and forward the appl	*/   4/* packet to the MAC layer with that information.	*/   1/*if (destination_address == OMSC_AA_AUTO_ASSIGN)   	{   7	// Initialize current destination address to the Auto    	// Assign value										     &	curr_dest_addr = destination_address;       3	// Call function to generate a random destination	   ,	// from the pool of available addresses.			   7	oms_aa_dest_addr_get (oms_aa_handle, &curr_dest_addr);       9	// Keep on generating the random addresses until source    /	// address is not same as current address.				   &	while (curr_dest_addr == mac_address)   		{   8		// Initialize current destination address to the Auto    		// Assign value										     '		curr_dest_addr = destination_address;       4		// Call function to generate a random destination	   -		// from the pool of available addresses.			   8		oms_aa_dest_addr_get (oms_aa_handle, &curr_dest_addr);   		}   	   	}   else   	{   /	// The packet needs to be sent to an explicit	   1	// destination as specified in the "Destination	   	// Address" attribute.							   &	curr_dest_addr = destination_address;   	}   */       '//Gathers the Ici sent along the packet   ici_dest_ptr = op_intrpt_ici();   :op_ici_attr_get(ici_dest_ptr,"dest_addr",&curr_dest_addr);       //Debug Purpose if No    if (ici_dest_ptr == NULL)   	op_pk_print(pkptr);       3/* Set this information in the interface control	*/   0/* information to be sent to the MAC layer.			*/   Cop_ici_attr_set (wlan_mac_req_iciptr, "dest_addr", curr_dest_addr);       3/* Install the control informationand send it to	*/   /* the MAC layer.									*/   %op_ici_install (wlan_mac_req_iciptr);   #op_pk_send (pkptr, outstrm_to_mac);    @  
                     
   ����   
          pr_state        :   �          
   mac layer arrival   
    @  
      8/* A packet arrived from the MAC layer. Since the MAC	*/   6/* layer would have forwarded this only if it were		*/   8/* destined for this node, forward this packet to the	*/   /* sink module.											*/       %//op_pk_send (op_pk_copy(pkptr) , 0);   op_pk_send (pkptr , 0);    @  
                     
   ����   
          pr_state        J   �          
   wait   
       
          
    @  
   ]   8/* Obtain the MAC layer information for the local MAC	*/   ./* process from the model-wide registry.				*/   4proc_record_handle_list_ptr = op_prg_list_create ();   ?oms_pr_process_discover (my_objid, proc_record_handle_list_ptr,   -	"node objid",	OMSC_PR_OBJID,		my_node_objid,   %	"protocol", 	OMSC_PR_STRING,		"mac",   
	OPC_NIL);       6/* If the MAC process regostered itself, then there	*/   !/* must be a valid match							*/   Irecord_handle_list_size = op_prg_list_size (proc_record_handle_list_ptr);   	   "if (record_handle_list_size !=  1)   	{   3	/* An error should be created if there are more	*/   3	/* than one WLAN-MAC process in the local node,	*/   $	/* or if no match is found.						*/   d	op_sim_end ("Error: either zero or several WLAN MAC processes found in the interface", "", "", "");   	}   else   	{   -	/*	Obtain a handle on the process record.	*/   ^	process_record_handle = (OmsT_Pr_Handle) op_prg_list_access (proc_record_handle_list_ptr, 0);       9	/* Obtain the module objid for the WLAN MAC module. 		*/   [	oms_pr_attr_get (process_record_handle, "module objid", OMSC_PR_OBJID, &mac_module_objid);       :	/* Obtain the stream numbers connected to and from the	*/   %	/* WLAN MAC layer process.								*/   _	oms_tan_neighbor_streams_find (my_objid, mac_module_objid, &instrm_from_mac, &outstrm_to_mac);       ?	/* Obtain the address handle maintained by the MAC process.	*/   ^	oms_pr_attr_get (process_record_handle, "address",             OMSC_PR_NUMBER,  &ne_address);   a	oms_pr_attr_get (process_record_handle, "auto address handle", OMSC_PR_ADDRESS, &oms_aa_handle);       :	/* Set the variable to indicate the MAC address of the	*/   )	/* associated MAC layer process.						*/    	mac_address = (int) ne_address;   	}               k//// NO DEST_ADDRESS VALIDATION : the destination address is specified in the packet, not arbitrarly !!!!!!                   F/* Check if the specified destination address (via the "Destination	*/   1/* Address" attribute) is valid or not.								*/       /*    (//Check for broadcast address.										   )if (destination_address == MAC_BROADCAST)   	{   	// Do Nothing	   	}   4else if (destination_address != OMSC_AA_AUTO_ASSIGN)   	{   */   	   C/*	// An explicit destination address has been specified. Check if	   $	// it is a valid address.										   .	if (destination_address == (int) mac_address)   		{   D		// Write a log stating that source node can not be a destination.    G		printf ("\n\nInvalid destination address specification. Changing\n");   d		printf ("the specification from its own MAC address (%d) to \"Random\"\n\n", destination_address);       @		// The destination address is set same as the lower layer MAC	   A		// address of this node. Ignore the original specification and    $		// and set it to random.										   ,		destination_address = OMSC_AA_AUTO_ASSIGN;   		}   	else   		{   B		// Checks if this is a valid address from the pool of addresses	   		// available.													       O		dest_addr_okay = oms_aa_dest_addr_check (oms_aa_handle, destination_address);   !		if (dest_addr_okay != OPC_TRUE)   			{       D		// Write a log stating that source node can not be a destination.    H			printf ("\n\nInvalid destination address specification. Changing\n");   P			printf ("the specification from %d, to \"Random\"\n\n", destination_address);       >			// The specified destination address is invalid. Set it to	   			// random.													   -			destination_address = OMSC_AA_AUTO_ASSIGN;   			}   		}   	}   */@  
           ����             pr_state         �   �          
   init2   
                     
      7/* Schedule a self interrupt to wait for lower layer	*/   4/* Wlan MAC process to finalize the MAC address			*/   (/* registration and resolution.							*/   ,op_intrpt_schedule_self (op_sim_time (), 0);   
           ����             pr_state      
              �   L     �   y  �   T     T             tr_14          
   APPL_LAYER_PKT_ARVL   
       ����              ����          
    ����   
                    pr_transition              �   ]        ]  �   ]  �   y             tr_16          ����          ����              ����          
    ����   
                    pr_transition              �   �     �   �  �   �     �             tr_17          
   MAC_LAYER_PKT_ARVL   
       ����              ����          
    ����   
                    pr_transition              �   �        �  �   �  �   �             tr_19          ����          ����              ����          
    ����   
                    pr_transition              �   �     f   �  �   �             tr_22          ����          ����              ����             ����                       pr_transition         
      �   �      v   �   �   �             tr_24          ����          ����              ����             ����                       pr_transition                 �      �   �  .   �             tr_28          ����          ����              ����             ����                       pr_transition                   outstat   d    ����   normal   linear        ԲI�%��}          oms_auto_addr_support   oms_pr   oms_tan          General Process Description: 
   ---------------------------- 
   FThe wlan_mac_higher_layer_intf process model accepts packets from any    Knumber of sources and discards them regardless of their content or format.
    
   ICI Interfaces: 
   -------------- 
   None 
   
   Packet Formats: 
   --------------- 
   None 
   
   Statistic Wires: 
   ---------------- 
   None 
   
   Process Registry: 
   ----------------- 
   Not Applicable
   
   Restrictions: 
   ------------- 
   None
        