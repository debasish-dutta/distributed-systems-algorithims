#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <vector>

#define PORT 8080

using namespace std;



// function for string delimiter
vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
   
int main(int argc, char const *argv[])
{

    srand((unsigned int)time(NULL)); // avoid always same output of rand()
    float client_local_clock = rand() % 10; // range from 0 to 9
    cout << "Client starts. Client pid is " << getpid() << endl;
    cout << "Client local clock is " << client_local_clock << endl;

    int client_socket_fd, valread;
    char client_read_buffer[1024] = {0};

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    // server_addr.sin_addr.s_addr = inet_addr(argv[1]); // hardcode to 127.0.0.1
    server_addr.sin_port = htons(PORT);  
    
    
    

    // Creating socket file descriptor (IPv4, TCP, IP)
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "\n Client: Socket creation error \n";
        return -1;
    }

       
    // Converting IPv4 and IPv6 addresses from text to binary form,
    //   from character string src into a network
    //   address structure in the af address family, then copies the
    //   network address structure to dst.
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0) 
    {
        cout << "\nClient: Invalid address/ Address not supported \n";
        return -1;
    }
   
    // Connecting server, return 0 with success, return -1 with error
    if (connect(client_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "\nClient: Connection Failed \n";
        return -1;
    }

    char server_ip[INET_ADDRSTRLEN]="";
    inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);
    cout << "Client: connected server(" << server_ip << ":" << ntohs(server_addr.sin_port) << ")." << endl;

    //
    // first round communicattion
    //

    //Asking server for its clock
    string msg_str = "Hello from client, please tell me your clock value";
    char msg_char_array[msg_str.length() + 1];
    strcpy(msg_char_array, msg_str.c_str());

    send(client_socket_fd , &msg_char_array , strlen(msg_char_array) , 0 );
    cout << "Client: sent message: '" << msg_char_array << "'\n";


    // convert char array to string
    string recv_msg = string(client_read_buffer);

    // receiving form server
    valread = read( client_socket_fd , client_read_buffer, 1024);
    cout << "Client: read: '" << client_read_buffer << "'" << endl;

    // convert char array to string
    recv_msg = string(client_read_buffer);

    if (recv_msg.find("From server, your clock adjustment offset is") != string::npos){ // if latter is a substring of former
        string substr_after_lastbutone_space;
        string substr_after_last_space;
        vector<string> split_str = split(recv_msg, " "); 
        substr_after_lastbutone_space = split_str[ split_str.size() - 2 ];
        substr_after_last_space = split_str[ split_str.size() - 1 ];

        cout << "Client: received local clock adjustment offset (string) is " << substr_after_lastbutone_space << " " << substr_after_last_space << endl;
        float substr_after_last_space_f = stof(substr_after_last_space);
        cout << "Client: received local clock adjustment offset (float) is " << substr_after_lastbutone_space << " " << substr_after_last_space_f << endl;

        char oper_char_array[substr_after_lastbutone_space.length() + 1];
        strcpy(oper_char_array, substr_after_lastbutone_space.c_str());
        if (strcmp(oper_char_array, "add") == 0 ){
            client_local_clock += substr_after_last_space_f;
        }else if (strcmp(oper_char_array, "minus") == 0 ){
            client_local_clock -= substr_after_last_space_f;
        }
        
        cout << "Client local clock is \n\n" << client_local_clock;
    }
    
    
    
    

    close(client_socket_fd);
    return 0;
}