MIL_3_Tfile_Hdr_ 81A 73B modeler 6 4098FF31 421EE147 10 ares-theo-1 Fabrice@Theoleyre 0 0 none none 0 0 none 675543D6 446E 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                              Ф═gЅ      8   L   |    #  	y  ь  n  5И  5└  AГ  A▒      node   WLAN       flm_red           Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                        Traffic Type of Service      wlan_mac_intf.Type of Service                                                                                Wireless LAN MAC Address      wireless_lan_mac.Address                                                                               Wireless LAN Parameters      (wireless_lan_mac.Wireless LAN Parameters                                                        count                                                                           list   	          	                                                               altitude      altitude                                                                                          phase      phase                                                                                          
TIM source            none      Wireless LAN MAC Address                 Auto Assigned      Wireless LAN Parameters         
      Default   
   altitude         
@Y             
   altitude modeling            relative to subnet-platform      	condition         
          
   financial cost            0.00      financial cost            0.00      financial cost            0.00      financial cost            0.00      financial cost            0.00      phase                           priority                        user id                                   ╚  R          
   wireless_lan_mac   
       
   wlan_mac   
          	processor                   Wireless LAN Parameters      ђ  
            count          
          
      list   	      .            	Data Rate         .Adч       11 Mbps   .      Physical Characteristics          .      Direct Sequence   .      Channel Settings      ђ  .            count                          list   	                ђ  .      PCF Parameters      ђ  .      Disabledђ  .   .ђ  
       ╩   ╚   џ          
   mewlana   
       
   mewlana_process   
          	processor                    ╬   ╚   Ш          
   wlan_mac_intf   
       
   process_wlan_mac_interface   
          	processor                	   █   l  «          
   wlan_port_rx0   
       
            count          
          
      list   	      
            	data rate         
A.ёђ           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
         	data rate         
A>ёђ           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
         	data rate         
ATч           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
         	data rate         
Adч           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
   
   
          bpsk          ?­                    
               
          
dra_ragain          
   
wlan_power   
          dra_bkgnoise             
dra_inoise             dra_snr             dra_ber          
   	dra_error   
       
   wlan_ecc   
          ra_rx                       nd_radio_receiver         reception end time         
           0.0   
          sec                                                               0.0                        !THIS ATTRIBUTE SHOULD NOT BE SET    TO ANY VALUE EXCEPT 0.0. This    "attribute is used by the pipeline     stages to determine whether the    receiver is busy or not. The    value of the attribute will be    updated by the pipeline stages    dynamically during the    simulation. The value will    "indicate when the receiver became    idle or when it is expected to    become idle.      С  $  «          
   wlan_port_tx0   
       
            count          
          
      list   	                  	data rate         
A.ёђ           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
      power         ?PbMмыЕЧ                	data rate         
A>ёђ           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
      power         ?PbMмыЕЧ                	data rate         
ATч           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
      power         ?PbMмыЕЧ                	data rate         
Adч           
      packet formats         
   wlan_control,wlan_mac   
      	bandwidth         
@Ј@            
      min frequency         
@б─            
      power         ?PbMмыЕЧ             
          bpsk          
   wlan_rxgroup   
       
   	dra_txdel   
       
   dra_closure_all   
       
   wlan_chanmatch   
          
dra_tagain          
   wlan_propdel   
          ra_tx                       nd_radio_transmitter          т   >   >          
   mobility   
       
   mobility_models   
          	processor                   endsim intrpt         
          
      priority          
           
                  С      ╦  ^    Г   
          strm_3          
   src stream [0]   
       
   dest stream [0]   
       
          
                                                                               nd_packet_stream             █          x  Х   ╩  ^   
          strm_4          
   src stream [0]   
       
   dest stream [0]   
       
          
                             
   0       
                                        nd_packet_stream             ╬          ╠     ╠  E   
          strm_12          
   src stream [1]   
       
   dest stream [5]   
       
          
                                                                               nd_packet_stream                 ╬      ┴  E   ┴     
          strm_13          
   src stream [5]   
       
   dest stream [1]   
       
          
                             
   0       
                                        nd_packet_stream                 С      м  ^    Б   
          strm_14          
   src stream [1]   
       
   dest stream [1]   
       
          
                                                                               nd_packet_stream             █          x  Г   ─  ^   
          strm_15          
   src stream [1]   
       
   dest stream [1]   
       
          
                             
   0       
                                        nd_packet_stream                 С      н  X    А   
          strm_16          
   src stream [2]   
       
   dest stream [2]   
       
          
                                                                               nd_packet_stream          	       С      н  Q  $  А   
          strm_17          
   src stream [3]   
       
   dest stream [3]   
       
          
                                                                               nd_packet_stream          
   █          x  ц   ╝  ]   
          strm_18          
   src stream [2]   
       
   dest stream [2]   
       
          
                             
   0       
                                        nd_packet_stream             █          p  А   ╗  V   
          strm_19          
   src stream [3]   
       
   dest stream [3]   
       
          
       
               
       
   0       
                                        nd_packet_stream            █          `  А   `  H   ╗  H          
   rxstat_11Mbps   
          channel [3]          
   radio receiver.received power   
          
instat [3]          
          
                             
           
       
           
       
           
       
           
       
               
       
=4АмW1└ў       
       
          
                                        nd_statistic_wire            С         )  А  )  J   н  J          
   txstat_5Mbps   
          channel [2]          
   radio transmitter.busy   
          
instat [4]          
          
                             
           
       
          
       
           
       
           
       
н▓IГ%ћ├}       
       
н▓IГ%ћ├}       
       
          
                                        nd_statistic_wire            С         ,  А  ,  G   н  F          
   txstat_11Mbps   
          channel [3]          
   radio transmitter.busy   
          
instat [4]          
          
                             
           
       
          
       
           
       
           
       
н▓IГ%ћ├}       
       
н▓IГ%ћ├}       
       
          
                                        nd_statistic_wire            █          d  А   d  M   ╗  M          
   rxstat_5Mbps   
          channel [2]          
   radio receiver.received power   
          
instat [2]          
          
                             
           
       
           
       
           
       
           
       
               
       
=4АмW1└ў       
       
          
                                        nd_statistic_wire            С         &  А  &  Q   н  P          
   txstat_2Mbps   
          channel [1]          
   radio transmitter.busy   
          
instat [4]          
          
                             
           
       
          
       
           
       
           
       
н▓IГ%ћ├}       
       
н▓IГ%ћ├}       
       
          
                                        nd_statistic_wire            С         "  А  "  V   н  T          
   txstat_1Mbps   
          channel [0]          
   radio transmitter.busy   
          
instat [4]          
          
                             
           
       
          
       
           
       
           
       
н▓IГ%ћ├}       
       
н▓IГ%ћ├}       
       
          
                                        nd_statistic_wire            █          g  А   h  Q   ╗  Q          
   rxstat_2Mbps   
          channel [1]          
   radio receiver.received power   
          
instat [1]          
          
                             
           
       
           
       
           
       
           
       
               
       
=4АмW1└ў       
       
          
                                        nd_statistic_wire            █          l  А   l  V   ╗  V          
   rxstat_1Mbps   
          channel [0]          
   radio receiver.received power   
          
instat [0]          
          
                             
           
       
           
       
           
       
           
       
               
       
=4АмW1└ў       
       
          
                                        nd_statistic_wire             ╬   ╩      ├   Ь   ├   ъ   
          strm_20             0             0                                                                                                   nd_packet_stream             ╩   ╬      ╦   а   ╩   Ш   
          strm_21             0             0                                                                                                   nd_packet_stream      В         &wireless_lan_mac.Backoff Slots (slots)   Backoff Slots (slots)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Rcvd (bits/sec)   Control Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Sent (bits/sec)   Control Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Rcvd (bits/sec)   Data Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Sent (bits/sec)   Data Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Sent (packets/sec)   Data Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   *wireless_lan_mac.Channel Reservation (sec)   Channel Reservation (sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Rcvd (packets/sec)   "Control Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Sent (packets/sec)   "Control Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Rcvd (packets/sec)   Data Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan    wireless_lan_mac.Load (bits/sec)   Load (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   wireless_lan_mac.Load (packets)   Load (packets)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   &wireless_lan_mac.Throughput (bits/sec)   Throughput (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Dropped Data Packets (bits/sec)   Dropped Data Packets (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   2wireless_lan_mac.Retransmission Attempts (packets)   !Retransmission Attempts (packets)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   3wireless_lan_mac.Dropped Data Packets (packets/sec)   "Dropped Data Packets (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   )wireless_lan_mac.Media Access Delay (sec)   Media Access Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan   )wireless_lan_mac.Hld Queue Size (packets)   Hld Queue Size (packets)           Wireless Lan   !bucket/default total/time average   linear   Wireless Lan   wireless_lan_mac.Delay (sec)   Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan          machine type       station   Model Attributes      8.1.A-Feb18-2002                interface type      
IEEE802.11           wlan_port_tx<n>   wlan_port_rx<n>           