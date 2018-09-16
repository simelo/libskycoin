%extend cipher__Address {
	char getVersion(){
		return $self->Version;
    }
    	void setVersion(char pValue){
		$self->Version = pValue;
    }
}

%extend cipher_Sig{

GoSlice toGoSlice(){
	GoSlice slice;
slice.len = sizeof(cipher_Sig);
slice.cap = sizeof(cipher_Sig)+1;
slice.data = (cipher_Sig*)&$self;
return slice;
	}
}
%extend GoSlice {
	int isEqual(GoSlice *slice){
		return (($self->len == slice->len)) && (memcmp($self->data,slice->data, sizeof(GoSlice_))==0 );
	}

	void convertString(char * data){
		$self->data = data;
		$self->len = strlen(data);
		$self->cap = strlen(data);
	}
}

%extend _GoString_ {
	int SetString(char * str){
		$self->p = str;
		$self->p = strlen(str);
	}
}