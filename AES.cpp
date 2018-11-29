#include <iostream>
#include <string>


int string_to_int(std::string str, int index){
if(str[index]=='a') return 10;
else if(str[index]=='b') return 11;
else if(str[index]=='c') return 12;
else if(str[index]=='d') return 13;
else if(str[index]=='e') return 14;
else if(str[index]=='f') return 15;
else return str[index]-48;
}

 void shift_array(std::string array[],int n){
	 std::string temp1=array[0];
	 std::string temp2=array[1];
         std::string temp3=array[2];

	 if(n==1){  // 1 2 3 4  2 3 4 1
       array[0]=array[1];	
       array[1]=array[2];	
       array[2]=array[3];	
       array[3]=temp1;	
	 }else if (n==2){
       array[0]=array[2];
       array[1]=array[3];
       array[2]=temp1;
       array[3]=temp2;
	 
	 }else if (n==3){// 1 2 3 4   4 1 2 3
       array[0]=array[3];
       array[1]=temp1;
       array[2]=temp2;
       array[3]=temp3;

         }

 
 }






std::string to_binary(int val){
switch(val){
        case(0): return "0000";
        case(1): return "0001";
        case(2): return "0010";
        case(3): return "0011";
        case(4): return "0100";
        case(5): return "0101";
        case(6): return "0110";
        case(7): return "0111";
        case(8): return "1000";
        case(9): return "1001";
        case(10): return "1010";
        case(11): return "1011";
        case(12): return "1100";
        case(13): return "1101";
        case(14): return "1110";
        case(15): return "1111";
        default: return"";
}
}


std::string shift_string(std::string str){
for(int i =0;i<7;i++){
str[i]=str[i+1];

}
str[7]='0';
return str;

}


std::string XOR(std::string s1, std::string s2){
for(int i=0;i<8;i++){
if(s1[i]==s2[i])
	s1[i]='0';
else s1[i]='1';

}
return s1;

}

std::string XOR_4(std::string a1,std::string a2,std::string a3,std::string a4){
return XOR(XOR(a1,a2),XOR(a3,a4));
}



std::string mul_2(std::string str){
	std::string s=to_binary(string_to_int(str,0))+to_binary(string_to_int(str,1));
	char c=s[0];
	s=shift_string(s);
	if(c=='1'){	 
	s=XOR(s,"00011011");
	}
return s;

}
std::string mul_3(std::string str){
        std::string s=to_binary(string_to_int(str,0))+to_binary(string_to_int(str,1));
        std::string ss=mul_2(str);
        s = XOR(s,ss);
return s;
}



std::string multiple_arrays(int array1[4],std::string array2[2]){
	std::string temp[4];
	
for(int i=0;i<4;i++){
	if(array1[i]==1){
	temp[i]=to_binary(string_to_int(array2[i],0))+to_binary(string_to_int(array2[i],1));
	} else if (array1[i]==2) {

       temp[i]=mul_2(array2[i]);

	}else if(array1[i]==3){

	temp[i]=mul_3(array2[i]);
	}
}
/*for(int i=0;i<4;i++){
	std::cout<<temp[i]<<std::endl;
}*/

return XOR_4(temp[0],temp[1],temp[2],temp[3]);

}



std::string to_hex(std::string str){
if (str=="0000") return "0";
else if(str=="0001") return "1";
else if(str=="0010") return "2";
else if(str=="0011") return "3";
else if(str=="0100") return "4";
else if(str=="0101") return "5";
else if(str=="0110") return "6";
else if(str=="0111") return "7";
else if(str=="1000") return "8";
else if(str=="1001") return "9";
else if(str=="1010") return "a";
else if(str=="1011") return "b";
else if(str=="1100") return "c";
else if(str=="1101") return "d";
else if(str=="1110") return "e";
else if(str=="1111") return "f";
else return "";
}



std::string hex(std::string str){
        std::string l;
        std::string r;
        l=str.substr (0,4);
        r=str.substr (4,7);
        std::string s=to_hex(l)+to_hex(r);

return s;
}





void mix_single_column(std::string input_state[4][4], int n){
int m1[4]= {2,3,1,1};
int m2[4]= {1,2,3,1};
int m3[4]= {1,1,2,3};
int m4[4]= {3,1,1,2};
   
std::string column[4];//;={"d4","bf","5d","30"};


for(int i=0;i<4;i++){
column[i]=input_state[i][n];
}

input_state[0][n]=hex(multiple_arrays(m1,column));
input_state[1][n]=hex(multiple_arrays(m2,column));
input_state[2][n]=hex(multiple_arrays(m3,column));
input_state[3][n]=hex(multiple_arrays(m4,column));



}







void substitute_bytes(std::string input_state[4][4], std::string s_box[16][16]){
 for(int i=0;i<4;i++)
                for(int j=0;j<4;j++){
                   input_state[i][j]=s_box[string_to_int(input_state[i][j],0)][string_to_int(input_state[i][j],1)];

              }


}
void substitute_byte(std::string input_state[4]){


     std::string s_box[16][16]={
              {"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
              {"ca","82","c9","7d","fa","59","47","f0","ad","d4","a2","af","9c","a4","72","c0"},
              {"b7","fd","93","26","36","3f","f7","cc","34","a5","e5","f1","71","d8","31","15"},
	      {"04","c7","23","c3","18","96","05","9a","07","12","80","e2","eb","27","b2","75"},
              {"09","83","2c","1a","1b","6e","5a","a0","52","3b","d6","b3","29","e3","2f","84"},
              {"53","d1","00","ed","20","fc","b1","5b","6a","cb","be","39","4a","4c","58","cf"},
              {"d0","ef","aa","fb","43","4d","33","85","45","f9","02","7f","50","3c","9f","a8"},
              {"51","a3","40","8f","92","9d","38","f5","bc","b6","da","21","10","ff","f3","d2"},
              {"cd","0c","13","ec","5f","97","44","17","c4","a7","7e","3d","64","5d","19","73"},
              {"60","81","4f","dc","22","2a","90","88","46","ee","b8","14","de","5e","0b","db"},
              {"e0","32","3a","0a","49","06","24","5c","c2","d3","ac","62","91","95","e4","79"},
              {"e7","c8","37","6d","8d","d5","4e","a9","6c","56","f4","ea","65","7a","ae","08"},
              {"ba","78","25","2e","1c","a6","b4","c6","e8","dd","74","1f","4b","bd","8b","8a"},
              {"70","3e","b5","66","48","03","f6","0e","61","35","57","b9","86","c1","1d","9e"},
              {"e1","f8","98","11","69","d9","8e","94","9b","1e","87","e9","ce","55","28","df"},
              {"8c","a1","89","0d","bf","e6","42","68","41","99","2d","0f","b0","54","bb","16"}
      };



 for(int i=0;i<4;i++)
                
                   input_state[i]=s_box[string_to_int(input_state[i],0)][string_to_int(input_state[i],1)];

              


}



void shift_rows(std::string input_state[4][4]){
  shift_array(input_state[1],1);
  shift_array(input_state[2],2);
  shift_array(input_state[3],3);

}


void mix_columns(std::string input_state[4][4]){
for(int i=0;i<4;i++){
mix_single_column(input_state,i);
}

}



void print(std::string state[4][4]){

  for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)
                        std::cout<<state[i][j]<<"  ";

                std::cout<<std::endl;
        }


}




void XOR_array(std::string arr1[4],std::string arr2[4], std::string arr3[4]){
	std::string temp1[4];
	std::string temp2[4];
	for(int i=0;i<4;i++){
	temp1[i]=to_binary(string_to_int(arr1[i],0))+to_binary(string_to_int(arr1[i],1));
	temp2[i]=to_binary(string_to_int(arr2[i],0))+to_binary(string_to_int(arr2[i],1));
	temp1[i]=XOR(temp1[i],temp2[i]);
        arr3[i]=hex(temp1[i]);

//	std::cout<<temp1[i]<<std::endl;
	}

}




void print_44(std::string state[4][44]){

  for(int i=0;i<4;i++){
                for(int j=0;j<44;j++)
                        std::cout<<state[i][j]<<"  ";

                std::cout<<std::endl;
        }


}


void get_column(std::string m[4][44], int n, std::string a[4]){
for(int i=0;i<4;i++){
a[i]=m[i][n];
}
}


void get_column_state(std::string m[4][4], int n, std::string a[4]){
for(int i=0;i<4;i++){
a[i]=m[i][n];
}
}


void get_column_rcon(std::string m[4][10], int n, std::string a[4]){
for(int i=0;i<4;i++){
a[i]=m[i][n];
}
}



void set_column(std::string m[4][44], int n, std::string a[4]){
for(int i=0;i<4;i++){
m[i][n]=a[i];
}
}


void set_column_state(std::string m[4][4], int n, std::string a[4]){
for(int i=0;i<4;i++){
m[i][n]=a[i];
}
}



void add_round_key(std::string state[4][4],std::string key[4][44], int n){
	std::string a[4];
	std::string b[4];
	for(int i=0;i<4;i++){
	get_column_state(state,i,a);
	get_column(key,n+i,b);
	XOR_array(a,b,a);
	set_column_state(state,i,a);
	
	}

}


int main(){

	std::string input_state[4][4];

std::string inputPl = "";
std::cout << "Please input the plaintext having length 32, example: 0123456789abcdeffedcba9876543210 " << std::endl;
std::cin >> inputPl;

for (int i = 0; i < 4; i++){
	for(int j = 0; j < 4; j++){
		input_state[j][i] = std::string() + inputPl.at(i * 8 + j*2) + inputPl.at(i * 8 + j*2 + 1);	

	}
}


       std::string initial_key[4][4];



std::string inputKey = "";
std::cout << "Please input the key in the following format: 0f1571c947d9e8590cb7add6af7f6798 " << std::endl;
std::cin >> inputKey;

for (int i = 0; i < 4; i++){
	for(int j = 0; j < 4; j++){
		initial_key[j][i] = std::string() + inputKey.at(i * 8 + j*2) + inputKey.at(i * 8 + j*2 + 1);	

	}
}

       std::string key[4][44];

        for(int i=0;i<4;i++)
	  for(int j=0;j<4;j++)
		  key[i][j]=initial_key[i][j];




 std::string rcon[4][10]={
                {"01","02","04","08","10","20","40","80","1b","36"},
                {"00","00","00","00","00","00","00","00","00","00"},
                {"00","00","00","00","00","00","00","00","00","00"},
                {"00","00","00","00","00","00","00","00","00","00"}
        };
//key scheduling
 std::string a[4];
 std::string b[4];
 std::string c[4];
for(int i=4;i<44;i++){
get_column(key,i-1,a);
get_column(key,i-4,b);
if(i%4==0){
shift_array(a,1);
substitute_byte(a);
get_column_rcon(rcon,(i-4)/4,c);
XOR_array(a,c,a);
}

XOR_array(a,b,a);
set_column(key,i,a);


}

//print_44(key);


      std::string s_box[16][16]={
	      {"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
	      {"ca","82","c9","7d","fa","59","47","f0","ad","d4","a2","af","9c","a4","72","c0"},
	      {"b7","fd","93","26","36","3f","f7","cc","34","a5","e5","f1","71","d8","31","15"},
	      {"04","c7","23","c3","18","96","05","9a","07","12","80","e2","eb","27","b2","75"},
	      {"09","83","2c","1a","1b","6e","5a","a0","52","3b","d6","b3","29","e3","2f","84"},
	      {"53","d1","00","ed","20","fc","b1","5b","6a","cb","be","39","4a","4c","58","cf"},
	      {"d0","ef","aa","fb","43","4d","33","85","45","f9","02","7f","50","3c","9f","a8"},
	      {"51","a3","40","8f","92","9d","38","f5","bc","b6","da","21","10","ff","f3","d2"},
	      {"cd","0c","13","ec","5f","97","44","17","c4","a7","7e","3d","64","5d","19","73"},
	      {"60","81","4f","dc","22","2a","90","88","46","ee","b8","14","de","5e","0b","db"},
	      {"e0","32","3a","0a","49","06","24","5c","c2","d3","ac","62","91","95","e4","79"},
	      {"e7","c8","37","6d","8d","d5","4e","a9","6c","56","f4","ea","65","7a","ae","08"},
	      {"ba","78","25","2e","1c","a6","b4","c6","e8","dd","74","1f","4b","bd","8b","8a"},
	      {"70","3e","b5","66","48","03","f6","0e","61","35","57","b9","86","c1","1d","9e"},
	      {"e1","f8","98","11","69","d9","8e","94","9b","1e","87","e9","ce","55","28","df"},
	      {"8c","a1","89","0d","bf","e6","42","68","41","99","2d","0f","b0","54","bb","16"}
      };


//print(input_state);
//std::cout<<std::endl;
add_round_key(input_state,key,0);
//print(input_state);
//std::cout<<std::endl;


for(int i=1;i<10;i++){
substitute_bytes(input_state,s_box);
shift_rows(input_state);
mix_columns(input_state);
add_round_key(input_state,key,4*i);
/*print(input_state);
std::cout<<std::endl;*/
}

substitute_bytes(input_state,s_box);
shift_rows(input_state);
add_round_key(input_state,key,40);


//print(input_state);
std::cout<<std::endl;

std::string resultString = "";

for (int i = 0; i < 4; i++){
	for(int j = 0; j < 4; j++){
		resultString = resultString + input_state[j][i];	

	}
}

std::cout << "The ciphertext is: " << resultString;

return 0;
}
