MIL_3_Tfile_Hdr_ 81A 73B modeler 6 40ADEC4C 43ED16F3 8 ares-theo-1 ftheoley 0 0 none none 0 0 none D4772934 5824 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                        ЋЭg      8   L     #  '  ­  	ч  !D  In  Iv  Uc  Ug      node   WLANџџџџ   mobile_commџџџџџџџџ   Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                        Wireless LAN MAC Address      wireless_lan_mac.Addressџџџџ    џџџџ           џџџџ          џџџџ          џџџџ                        altitude      altitudeџџџџ   џџџџ               џџџџ              џџџџ              џџџџ                        phase      phaseџџџџ   џџџџ               џџџџ              џџџџ              џџџџ                        
TIM source            none      Wireless LAN MAC Address                 Auto Assigned      altitude         
        џџџџ   
   altitude modeling            relative to subnet-platform      	condition         
   џџџџ   
   financial cost            0.00      financial cost            0.00      financial cost            0.00      financial cost            0.00      financial cost            0.00      phase                 џџџџ      priority              џџџџ      user id              џџџџ      	           Ш  R          
   wireless_lan_mac   
       
   wlan_mac   
          	processor                   Wireless LAN Parameters   џџџ  
            count    џџџ   
   џџџџ   
      list   	џџџ   .            	Data Rate   џџџ   .Adћ       11 Mbps   .      Physical Characteristics    џџџ   .      Direct Sequence   .      Channel Settings   џџџ  .            count    џџџ      џџџџ         list   	џџџ               .      PCF Parameters   џџџ  .      Disabled  .   .  
       Ъ   Ш             
   cbrp   
       
   cbrp_process   
          	processor                    Ю   Ш   і          
   wlan_mac_intf   
       
   process_wlan_mac_interface   
          	processor                	   л   l  Ў          
   wlan_port_rx0   
       
            count    џџџ   
   џџџџ   
      list   	џџџ   
            	data rate   џџџ   
A.    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
         	data rate   џџџ   
A>    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
         	data rate   џџџ   
ATћ    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
         	data rate   џџџ   
Adћ    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
   
   
          bpsk          ?№      џџџџ          
        џџџџ   
          
dra_ragain          
   
wlan_power   
          dra_bkgnoise             
dra_inoise             dra_snr             dra_ber          
   	dra_error   
       
   wlan_ecc   
          ra_rx                       nd_radio_receiver         reception end time   џџџ   
           0.0   
џџџџ      sec              џџџџ              џџџџ              џџџџ         0.0           џџџџ         !THIS ATTRIBUTE SHOULD NOT BE SET    TO ANY VALUE EXCEPT 0.0. This    "attribute is used by the pipeline     stages to determine whether the    receiver is busy or not. The    value of the attribute will be    updated by the pipeline stages    dynamically during the    simulation. The value will    "indicate when the receiver became    idle or when it is expected to    become idle.      ф  $  Ў          
   wlan_port_tx0   
       
            count    џџџ   
   џџџџ   
      list   	џџџ               	data rate   џџџ   
A.    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
      power   џџџ   ?PbMвёЉќџџџџ            	data rate   џџџ   
A>    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
      power   џџџ   ?PbMвёЉќџџџџ            	data rate   џџџ   
ATћ    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
      power   џџџ   ?PbMвёЉќџџџџ            	data rate   џџџ   
Adћ    џџџџ   
      packet formats   џџџ   
   wlan_control,wlan_mac   
      	bandwidth   џџџ   
@@     џџџџ   
      min frequency   џџџ   
@ЂФ     џџџџ   
      power   џџџ   ?PbMвёЉќџџџџ         
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
          ra_tx                       nd_radio_transmitter          ќ  м   і          
   eth_mac_intf   
       
   process_ethernet_mac_interface   
          	processor                   high dest address    џџџ   
џџџў   Maximum Dest Address   
      low dest address    џџџ   
џџџў   Minimum Dest Address   
      §  м  R          
   mac_0   
       
   ethernet_mac_v2   
          queue                   MAC Parameters   џџџ  
            count    џџџ   
   џџџџ   
      list   	џџџ   
            Address    џџџ   
џџџў   Auto Assigned   
      Promiscuous Mode   џџџ   
      Enabled   
   
  
      subqueue   џџџ  
            count    џџџ   
   џџџџ   
      list   	џџџ   
                      
  
      ў  Ў  Ў          
   hub_rx0   
       
            count    џџџ   
   џџџџ   
      list   	џџџ   
            	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
   
   
               џџџџ             pt_rx                       nd_ptp_receiver         џ  
  Ў          
   hub_tx0   
       
            count    џџџ   
   џџџџ   
      list   	џџџ   
            	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
         	data rate   џџџ   
двI­%У}џџџџ   
      packet formats   џџџ   
   ethernet_v2   
   
   
          pt_tx                       nd_ptp_transmitter      #               ф      Ы  ^    ­   
          strm_3          
   src stream [0]   
       
   dest stream [0]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream             л          x  Ж   Ъ  ^   
          strm_4          
   src stream [0]   
       
   dest stream [0]   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream             Ю          Ь     Ь  E   
          strm_12          
   src stream [1]   
       
   dest stream [5]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream                 Ю      С  E   С     
          strm_13          
   src stream [5]   
       
   dest stream [1]   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream                 ф      в  ^    Ѓ   
          strm_14          
   src stream [1]   
       
   dest stream [1]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream             л          x  ­   Ф  ^   
          strm_15          
   src stream [1]   
       
   dest stream [1]   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream                 ф      д  X    Ё   
          strm_16          
   src stream [2]   
       
   dest stream [2]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          	       ф      д  Q  $  Ё   
          strm_17          
   src stream [3]   
       
   dest stream [3]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          
   л          x  Є   М  ]   
          strm_18          
   src stream [2]   
       
   dest stream [2]   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream             л          p  Ё   Л  V   
          strm_19          
   src stream [3]   
       
   dest stream [3]   
       
   џџџџ   
       
        џџџџ   
       
   0џџџџ   
                                        nd_packet_stream            л          `  Ё   `  H   Л  H          
   rxstat_11Mbps   
          channel [3]          
   radio receiver.received power   
          
instat [3]          
   џџџџ   
               џџџџ          
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
        џџџџ   
       
=4ЁвW1Рџџџџ   
       
   џџџџ   
                                        nd_statistic_wire            ф         )  Ё  )  J   д  J          
   txstat_5Mbps   
          channel [2]          
   radio transmitter.busy   
          
instat [4]          
   џџџџ   
               џџџџ          
    џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire            ф         ,  Ё  ,  G   д  F          
   txstat_11Mbps   
          channel [3]          
   radio transmitter.busy   
          
instat [4]          
   џџџџ   
               џџџџ          
    џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire            л          d  Ё   d  M   Л  M          
   rxstat_5Mbps   
          channel [2]          
   radio receiver.received power   
          
instat [2]          
   џџџџ   
               џџџџ          
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
        џџџџ   
       
=4ЁвW1Рџџџџ   
       
   џџџџ   
                                        nd_statistic_wire            ф         &  Ё  &  Q   д  P          
   txstat_2Mbps   
          channel [1]          
   radio transmitter.busy   
          
instat [4]          
   џџџџ   
               џџџџ          
    џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire            ф         "  Ё  "  V   д  T          
   txstat_1Mbps   
          channel [0]          
   radio transmitter.busy   
          
instat [4]          
   џџџџ   
               џџџџ          
    џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire            л          g  Ё   h  Q   Л  Q          
   rxstat_2Mbps   
          channel [1]          
   radio receiver.received power   
          
instat [1]          
   џџџџ   
               џџџџ          
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
        џџџџ   
       
=4ЁвW1Рџџџџ   
       
   џџџџ   
                                        nd_statistic_wire            л          l  Ё   l  V   Л  V          
   rxstat_1Mbps   
          channel [0]          
   radio receiver.received power   
          
instat [0]          
   џџџџ   
               џџџџ          
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
    џџџџ   
       
        џџџџ   
       
=4ЁвW1Рџџџџ   
       
   џџџџ   
                                        nd_statistic_wire             Ю   Ъ      У   ю   У      
          strm_20             0             0             џџџџ                  џџџџ             џџџџ                                           nd_packet_stream             Ъ   Ю      Ы       Ъ   і   
          strm_21             0             0             џџџџ                  џџџџ             џџџџ                                           nd_packet_stream          g   §   џ     ш  ]    Ё   
          strm_5          
   0   
       
   0   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          h   ў   §     Ж  Ё  б  ^   
          strm_6          
   0   
       
   0   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream          i   ќ   §     т    т  E   
          strm_7          
   src stream [1]   
       
   1   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream          j   §   ќ     ж  E  ж     
          strm_8          
   src stream [1]   
       
   dest stream [1]   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          k   §   џ     ф  ^  ў  Ђ   
          strm_10          
   2   
       
   1   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          l   §   џ     ш  P    Ё   
          strm_11          
   3   
       
   2   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          m   §   џ     п  ^  §  Ў   
          strm_24          
   4   
       
   3   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream          n   ў   §     ­  Ё  Я  W   
          strm_25          
   1   
       
   2   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream          o   ў   §     К  Џ  м  ^   
          strm_26          
   2   
       
   3   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream          p   ў   §     К  Ј  е  ^   
          strm_27          
   3   
       
   4   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream         q   ў   §     Љ  Ё  Љ  T  Я  T          
   st_2   
          channel [0]          
   point-to-point receiver.busy   
          
instat [0]          
   џџџџ   
               џџџџ          
   џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire         r   џ   §       Ё    Q  ш  Q          
   stat_0   
          channel [0]          
   point-to-point transmitter.busy   
          
instat [1]          
   џџџџ   
               џџџџ          
    џџџџ   
       
   џџџџ   
       
    џџџџ   
       
    џџџџ   
       
дВI­%У}џџџџ   
       
дВI­%У}џџџџ   
       
   џџџџ   
                                        nd_statistic_wire         s   ў   џ     К  Ў  §  Ў          
   Ethernet (P0)   
          8џџџџ                                           nd_association          w   ќ   Ъ     т   ю   Ч      
          strm_9          
   src stream [0]   
       
   2   
       
   џџџџ   
               џџџџ          
   0џџџџ   
                                        nd_packet_stream          x   Ъ   ќ      У     б   є   
          strm_28          
   2   
       
   0   
       
   џџџџ   
               џџџџ             џџџџ                                           nd_packet_stream        z      &wireless_lan_mac.Backoff Slots (slots)   Backoff Slots (slots)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Rcvd (bits/sec)   Control Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Sent (bits/sec)   Control Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Rcvd (bits/sec)   Data Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Sent (bits/sec)   Data Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Sent (packets/sec)   Data Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   *wireless_lan_mac.Channel Reservation (sec)   Channel Reservation (sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Rcvd (packets/sec)   "Control Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Sent (packets/sec)   "Control Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Rcvd (packets/sec)   Data Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan    wireless_lan_mac.Load (bits/sec)   Load (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   wireless_lan_mac.Load (packets)   Load (packets)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   &wireless_lan_mac.Throughput (bits/sec)   Throughput (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Dropped Data Packets (bits/sec)   Dropped Data Packets (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   2wireless_lan_mac.Retransmission Attempts (packets)   !Retransmission Attempts (packets)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   3wireless_lan_mac.Dropped Data Packets (packets/sec)   "Dropped Data Packets (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   )wireless_lan_mac.Media Access Delay (sec)   Media Access Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan   )wireless_lan_mac.Hld Queue Size (packets)   Hld Queue Size (packets)           Wireless Lan   !bucket/default total/time average   linear   Wireless Lan   wireless_lan_mac.Delay (sec)   Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan          machine type       station   Model Attributes      8.1.A-Feb18-2002                interface type      
IEEE802.11           wlan_port_tx<n>   wlan_port_rx<n>           