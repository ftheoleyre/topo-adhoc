MIL_3_Tfile_Hdr_ 81A 40A modeler 40 43159C6E 43159C6F 2 ares-theo-1 ftheoley 0 0 none none 0 0 none 98D8C257 CA6 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                      ����             0x0             NONE                                       *          
   Type   
                        integer             signed, big endian          
   8   
       
   3   
       
   set   
          NONE             *����             1                       pk_field      n      *          
   N   
    @  
      5No delete flag; set when a node has performed a local   6repair of a link, and upstream nodes should not delete   
the route.@  
          integer             signed, big endian          
   1   
       
   0   
       
   set   
          NONE             *����             2                       pk_field      �      *          
   Reserved   
    @  
       Sent as 0; ignored on reception.@  
          integer             signed, big endian          
   15   
       
   0   
       
   set   
          NONE             *����             3                       pk_field     @      *          
   	DestCount   
    @  
      6The number of unreachable destinations included in the   message; MUST be at least 1.@  
          integer             signed, big endian          
   8   
       
   1   
          set             NONE             *����             4                       pk_field         <   *          
   UnreachableDestinations   
    @  
      +Unreachable Destination IP Address (32bits)   2	The IP address of the destination that has become   !	unreachable due to a link break.       0Unreachable Destination Sequence Number (32bits)   1	The sequence number in the route table entry for   3	the destination listed in the previous Unreachable   	Destination IP Address field.@  
       
   packet   
          signed, big endian          
   	inherited   
       
����   
       
   unset   
          NONE             *����             5                       pk_field         �   *          
   NextHop   
                     
   integer   
          signed, big endian             32          ����          
   unset   
          NONE             *����             6                   �   *          
   PrevHop   
                        integer             signed, big endian             32          ����          
   unset   
          NONE             *����             7                   �   *          
   StatId   
                        integer             signed, big endian             32          ����          
   unset   
          NONE             *����             8                       pk_field   