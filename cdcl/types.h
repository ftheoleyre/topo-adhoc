//--------------------------------------------
//
//				CONSTANTS
//
//--------------------------------------------

#define		MAX_NB_NODES		100


#define		OPC_LISTPOS_TAIL	-1
#define		OPC_LISTPOS_HEAD	0


#define		OPC_FALSE			0
#define		OPC_TRUE			1



#define		INFINITY_SHORT		128




//--------------------------------------------
//
//			STRUCTURES / VARIABLES
//
//--------------------------------------------


typedef struct {
	void*	elem;
	struct List	*next;
} List;

typedef short	Boolean;
