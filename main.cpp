#include <bits/stdc++.h>
using namespace std;

int main()
{
     std::ifstream file("input.txt");
     std::string str;
     string temp;
     
     int maxi=0;

     set<int>s;
     set<int>::iterator itr;

     map<int,pair<int,string>>mp1; //slot - {age, reg_no}
     map<int,vector<int>>mp2; //age - slot numbers
     map<int,vector<string>>mp3; //age - reg_no
     map<string,int>mp4; //reg_no - slot
     
     while (std::getline(file, str)) 
     {
          // std::cout << str << "\n";
          if(str.substr(0,18)=="Create_parking_lot")
          {
               temp=str.substr(19,str.length()-19);
               maxi=stoi(temp);
               cout<<"Created parking of "<<maxi<<" slots"<<'\n';
               for(int i=1;i<=maxi;i++)
               {
                 s.insert(i);
               }
          }
          else if(str.substr(0,4)=="Park")
          {
            string reg_no=str.substr(5,13);
            string temp2=str.substr(30,str.length()-30);
            int age=stoi(temp2);

            if(s.size()==0)
            {
              cout<<'\n';
              continue;
            }
            itr=s.begin();
            int idx=*itr;

            mp1[idx]={age, reg_no};
            mp2[age].push_back(idx);
            mp3[age].push_back(reg_no);
            mp4[reg_no]=idx;

            s.erase(itr);

            cout<<"Car with vehicle registration number "<<'"'<<reg_no<<'"'<<" has been parked at slot number "<<idx<<'\n';
          }
          else if(str.substr(0,30)=="Slot_numbers_for_driver_of_age")
          {
            string temp2=str.substr(31,str.length()-31);
            int age=stoi(temp2);
            string res="";
            for(auto k:mp2[age])
            {
              if(s.find(k)==s.end())
              {
                res+=to_string(k);
                res+=',';
              }
            }
            if(res.size()==0)
            {
              cout<<'\n';
              continue;
            }
            else
            {
              cout<<res.substr(0,res.length()-1)<<'\n';
            }
          }
          else if(str.substr(0,31)=="Slot_number_for_car_with_number")
          {
            string reg_no=str.substr(32,13);
            cout<<mp4[reg_no]<<'\n';
          }
          else if(str.substr(0,5)=="Leave")
          {
            string temp2=str.substr(6,str.length()-6);
            int slot=stoi(temp2);
            if(s.find(slot)!=s.end())
            {
              cout<<"Slot already vacant"<<'\n';
              continue;
            }

            int age=mp1[slot].first;
            string reg_no=mp1[slot].second;

            s.insert(slot);
            mp4[reg_no]=-1;

            cout<<"Slot number "<<slot<<" vacated, the car with vehicle registration number "<<'"'<<reg_no<<'"'<<" left the space, the driver of the car was of age "<<age<<'\n';
          }
          else if(str.substr(0,45)=="Vehicle_registration_number_for_driver_of_age")
          {
            string temp2=str.substr(46,str.length()-46);
            int age=stoi(temp2);

            string res="";

            for(auto k:mp3[age])
            {
              if(mp4[k]!=-1)
              {
              res+=k;
              res+=',';
              }
            }
            if(res.size()==0)
            {
              cout<<'\n';
              continue;
            }
            else
            {
              cout<<res.substr(0,res.size()-1)<<'\n';
            }
          }
     }
    return 0;
}