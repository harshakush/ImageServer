#ifndef SERVER_OPERATION_TYPES
#define SERVER_OPERATION_TYPES


class ServerOperationTypes {
	
public:
	enum class rest_methods { 
		IGET =0, 
		IPOST =1,
		IPUT=2, 
		IDELETE =3
	};

	typedef rest_methods rest_operation;
};

#endif