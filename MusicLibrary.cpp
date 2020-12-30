#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<array>
#include<vector>
#include<math.h>
#include<sstream>
#define SONGMAX 1024
using namespace std;
struct Song{
    string title;
    string artist;
    int year_published;
};
//declare variable
string tit;
string art;
string year;
int int_year;
string item_to_search;
string item_to_delete;
struct Song music_library[SONGMAX];
int current_number_of_songs=0;
bool terminal_print=true;
int userinput;
ifstream myfile;
string musicList;
string delimiter = ":";
string delimiter2 = ",";
string title_memory;
string artist_memory;
int year_memory;
int counter=0;

//for quick sort
// consult the wikipedia page on quick sort algorithm.
int partition(int low, int high){
    string pivot = music_library[high].title;
    int i = low;
    for (int j=low; j<=high;j++){
        // get the first character of the title. for sorting, change all of them into lower case.
        if(tolower(music_library[j].title[0])<tolower(pivot[0])){
            swap(music_library[i],music_library[j]);
            i=i+1;
        }
    }
    swap(music_library[i],music_library[high]);
    return i;
}

void quick_sort(int low, int high){
    //when current_number_of_songs is greater than 1
    if(low<high){
         int p = partition(low, high);
         quick_sort(low,p-1);
         quick_sort(p+1,high);

    }

}


//Given the return type of the getchar, I decided to represent the user's command input as integers.
int read_command(){
    userinput=getchar();
         while(userinput==10 || userinput==32 || userinput==9 ){
            userinput=getchar();
    };
    
        return userinput;
};

//bool is for whether the user want the line number or not
void print_MusicLibrary(bool a){
    if (a){
        for (int i=0; i<current_number_of_songs; i++){
            cout<<i+1<<" Title: "<<music_library[i].title<<" Artists: "<< music_library[i].artist<<" Year Published: "<<music_library[i].year_published<<"\n";

        };
    }else{
        for (int i=0; i<current_number_of_songs; i++){
            cout<<" Title: "<<music_library[i].title<<" Artists: "<< music_library[i].artist<<" Year Published: "<<music_library[i].year_published<<"\n";

    }
};

}
   
void load_MusicLibrary(){
        music_library[counter].title=title_memory;
        music_library[counter].artist=artist_memory;
        music_library[counter].year_published=year_memory;
        counter=counter+1;
    
};

void store_MusicLibrary(){
    ofstream myfile;
    myfile.open("myMusic");
    if(myfile.is_open()){
        for (int i=0; i<current_number_of_songs; i++){
            myfile<<"Title: "<<music_library[i].title<<", "<<"Artists: "<<music_library[i].artist<<", "<<"Year Published: "<<music_library[i].year_published<<"\n";//write to the file

   };
   }
    else cout<<"unable to open the file\n";
   

};
char char_title[1024];//the maximum length
char char_target[1024];//declare the length

int find_index_of_song_with_name(string a){
    int L = 0;
    int R = current_number_of_songs-1;
    int middle;
    strcpy(char_target,a.c_str());
    while (L<=R){
        middle = floor((L+R)/2);
        strcpy(char_title,music_library[middle].title.c_str());//learn from C++.com, how to use c_str() copy the string value to the str2
        //make all lowercase
        for(int i=0;i<sizeof(char_title);i++){
            char_title[i]=tolower(char_title[i]);

        }
         for(int i=0;i<sizeof(char_target);i++){
            char_target[i]=tolower(char_target[i]);
        }
        if(strcmp (char_target,char_title)>0){
            L=middle+1;
        }else if (strcmp (char_target,char_title)<0){
            R=middle-1;
        }else
        {
            return middle;
        }
    }
    return -1;

};
/*
//design a different find function for adding only because adding 
//function requires the sorting algorithm to be able to figure out where an
//element is supposed to be inserted before an element is inserted. In order to do that, 
I choose to let the binary algorithm run, then, when the algorithm exhaust all elements in the array
 the end iterator will point at the position where the element need to be inserted.
*/
int find_index_of_song_with_name_to_add(string a){
    
    int L = 0;
    int R = current_number_of_songs-1;
    int middle;
    strcpy(char_target,a.c_str());
    while (L<=R){
        middle = floor((L+R)/2);
        //change target string into char
        //learn from C++.com, how to use c_str() copy the string value to the str2
        strcpy(char_title,music_library[middle].title.c_str());
        char_title[0]=tolower(char_title[0]);
        char_target[0]=tolower(char_target[0]);
        if(strcmp (char_target,char_title)>0){
            L=middle+1;
        }else if (strcmp (char_target,char_title)<0){
            R=middle-1;
        }else
        { 
            return middle;
        }
    }
    
    return middle;

};

void crunch_down_from_index(int index){
    if(current_number_of_songs>1){
    for (int i=current_number_of_songs-1;i>=index;i--){
        swap(music_library[i],music_library[i+1]);
    };
    
    }if (current_number_of_songs<=1){
        swap(music_library[0],music_library[1]);
    }

};

void crunch_up_from_index(int index){
    if(current_number_of_songs>1){
        for (int i =index; i<current_number_of_songs;i++){
            swap(music_library[i],music_library[i+1]);
        };   
        music_library[current_number_of_songs-1]={};//set the last element to 0.
    }if(current_number_of_songs<=1){
        swap(music_library[0],music_library[1]);
        music_library[1]={};//set the last element to 0.
    }

};


int index_to_delete;
void remove_song_from_MusicLibrary_by_name(string a){
    index_to_delete=find_index_of_song_with_name(a);
    if(index_to_delete==-1){
        cout<<"the element you provided is not present in the library\n";
    }
    else{
        crunch_up_from_index(index_to_delete);    
        current_number_of_songs=current_number_of_songs-1;

    }
};

int index_to_add;
void add_song_to_MusicLibrary_by_name(string a){
    index_to_add=find_index_of_song_with_name_to_add(a);
    crunch_down_from_index(index_to_add);    
};
void write_song(int index)
{ 
        music_library[index].title=tit;
        music_library[index].artist=art;
        music_library[index].year_published=int_year;
}

void get_substring_for_musiclib(){
    title_memory =string(musicList.c_str()+musicList.find(delimiter)+2,musicList.c_str()+ musicList.find(delimiter2));   
    musicList=musicList.substr(musicList.find(delimiter2)+2,musicList.size()-musicList.find(delimiter2)-2);
    artist_memory=string(musicList.c_str()+musicList.find(delimiter)+2,musicList.c_str()+ musicList.find(delimiter2));
    musicList=musicList.substr(musicList.find(delimiter2)+2,musicList.size()-musicList.find(delimiter2)-2);
    year_memory=stoi(string(musicList.c_str()+musicList.find(delimiter)+2,musicList.c_str()+ musicList.size()));


}
void read_song(){
    myfile.open("myMusic");
    if(myfile.is_open()){
        while (getline(myfile, musicList))//receive help from stack overflow.com "using getline() to read the whole file"
        {
        get_substring_for_musiclib();
        load_MusicLibrary();    
        }
    }  
}
void get_the_input(){
        cout<<"Title : ";
        cin.ignore();
        getline(cin,tit);
        cout<<"Artist : ";
        getline(cin,art);
        cout<<"Year : ";
        getline(cin,year);
        stringstream(year)>>int_year;
}

void evaluate_command(int a){
    if(a==105|| a==73){//command i
        get_the_input();
        //when there is no song in the library
        if(current_number_of_songs==0){
            write_song(0);
        }else{
        //already songs in the libray
            add_song_to_MusicLibrary_by_name(tit);
            write_song(index_to_add);
        }
        current_number_of_songs=current_number_of_songs+1;
        //sort an array after inserting new elements using quick sort
        //because quick_sort requires low< high, so when a special case is needed when we have only one element.
        if(current_number_of_songs==1){
            evaluate_command(read_command());
        }else if(current_number_of_songs>1){
            quick_sort(0,current_number_of_songs-1);
            evaluate_command(read_command());
        }
    }
    else if(a==113|| a==81){ //command q
        // add the save files
        store_MusicLibrary();
        cout<<"quit is being met\n";
        
    }
    else if(a==112 ||a==80){//command p
        print_MusicLibrary(terminal_print);
        evaluate_command(read_command());
    }
    else if(a==76||a==108){//command L
    int index1;
    cout<<"Title: ";
    cin.ignore();
    getline(cin, item_to_search);

    if(find_index_of_song_with_name(item_to_search)==-1){
        cout<<"the music you wanna find is not here. Please re-enter command\n";
        evaluate_command(read_command());
    }else
    {
        index1=find_index_of_song_with_name(item_to_search);
        cout<<" Title: "<<music_library[index1].title<<" Artists: "<< music_library[index1].artist<<" Year Published: "<<music_library[index1].year_published<<"\n";
        evaluate_command(read_command());
        }
    item_to_search="";
    }
    else if(a==68||a==100){//command D
    cout<<"Title: ";
    cin.ignore();
    getline(cin,item_to_delete);
    remove_song_from_MusicLibrary_by_name(item_to_delete);
    evaluate_command(read_command());
    }

    else{//if the user input something else.
        cout<<"Could not recognize the command, please re-enter\n";
        evaluate_command(read_command());
    }
};



int main(){
    evaluate_command(read_command());
   

}

