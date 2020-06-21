#include<bits/stdc++.h>
#include<fstream>
using namespace std;

struct drink{ //自訂資料型別為drink
    string drink_name; //飲料名稱
    int price; //價格
    int cost; //成本
    int stock;//庫存
};

void wrt_back_file(vector<drink> &drinks){
    ofstream fout("inventory.txt");
    for(int i=0;i<drinks.size();++i){
        fout<<drinks[i].drink_name<<","<<drinks[i].price<<","<<drinks[i].cost<<","<<drinks[i].stock;
        if(i!=drinks.size()-1){
            fout<<endl;
        }
    }
    fout.close();
    return ;
}//將更新內容寫回檔案裡方便下此讀檔時資料不會有錯誤

bool cmp(pair<string,int> &tmp1,pair<string,int>  &tmp2){
    return tmp1.second>tmp2.second;
}// sort中的自定義compare function

long long int total_sum=0;
vector<pair<string,int> >rec;
// 儲存目前總營業額
//儲存目前購買紀錄 開在global是因為避免資料被洗掉

int main(){
    bool flag=true;
    // 方便rec所使用的boolean

    while(true){

        cout<<"Welcome! ^^"<<endl<<endl;
        vector<drink> drinks;
        //儲存目前的所有商品的狀態 寫檔較為方便
        int cnt=0;
        ifstream fin("inventory.txt");
        //開檔
        while(!fin.eof()){
            string str,tmp_str;
            drink tmp_drink;
            //暫存性質的struct 方便推進vector中
            int index=0;
            fin>>str;
            for(int i=0;i<str.length();i++){
                if(str[i]==','){
                    str[i]=' ';
                }
            }//將所有逗號換為空白 方便切割字串取得所需資料
            stringstream ss;//切割字串用
            ss<<str;
            ss>>tmp_drink.drink_name>>tmp_drink.price>>tmp_drink.cost>>tmp_drink.stock;
            //切割出各項資料
            if(flag){
                rec.push_back(make_pair(tmp_drink.drink_name,0));
            }
            drinks.emplace_back(tmp_drink);
            ++cnt;
            cout<<cnt<<". "<<"name:"<<tmp_drink.drink_name<<" "<<"price:$"<<tmp_drink.price;
            if(tmp_drink.stock<5 && tmp_drink.stock!=0){
                cout<<"(stock<5)"<<endl;
            }
            else if(tmp_drink.stock==0){
                cout<<"(out of stock)"<<endl;
            }
            else{
                cout<<endl;
            }//輸出各個狀態訊息
        }
        flag=false;
        fin.close();
        //關檔

        cout<<endl;
        cout<<"type the index number of drink you want or type '0' for admine interface :";
        int type_num;
        cin>>type_num;
        cout<<endl;

        if(type_num>0 && type_num<=drinks.size()){ 
            cout<<"You want to buy:"<<drinks[type_num-1].drink_name<<endl;
            if(drinks[type_num-1].stock==0){
                cout<<"It is out of stoke"<<endl;
                continue;
            }
            // 輸出與輸入
            int coin_1,coin_5,coin_10;
            cout<<"ple insert coin of three type respectivily"<<endl<<endl;;
            cout<<"$10: ";
            cin>>coin_10;
            cout<<"$5: ";
            cin>>coin_5;  
            cout<<"$1: ";
            cin>>coin_1;
            cout<<endl;

            long long int sum=10*coin_10+5*coin_5+coin_1;
            cout<<"Sum of your insert Money: "<<sum<<endl;
            if(sum>=drinks[type_num-1].price && drinks[type_num-1].stock!=0){
                cout<<"Congratulations! You get drinks!"<<endl;
                cout<<"Return Money:"<<sum-drinks[type_num-1].price<<endl<<endl;
                --drinks[type_num-1].stock;
                total_sum+= (drinks[type_num-1].price - drinks[type_num-1].cost);
                for(auto &t:rec){
                    if(t.first==drinks[type_num-1].drink_name){
                        ++t.second;
                        break;
                    }
                }
                //購買成功 更新商品各項資料
                wrt_back_file(drinks); // 寫回檔案
                continue;
            }
            else{   
                //購買失敗
                cout<<"Yout money is Not enough to buy =("<<endl;
                cout<<"Return Money:"<<sum<<endl<<endl;
                continue;
            }
        }
        else if(type_num==0){ //for admin
            cout<<"Hi admin"<<endl;
            cout<<"1. Update the price of an item"<<endl;
            cout<<"2. Update the value of the stock of the an item"<<endl;
            cout<<"3. Show the profits"<<endl;
            cout<<"4. Go back to the initial screen"<<endl<<endl;
            int admin_num;
            cout<<"choose: ";
            cin>>admin_num;
            //管理者的界面
            cout<<endl;

            if(admin_num==1){
                cout<<"Item name you want to change:";
                string tmp;
                int new_price;
                cin>>tmp;
                cout<<"new Item Price you want:";
                cin>>new_price;
                for(auto &t:drinks){
                    if(t.drink_name==tmp){
                        t.price=new_price;
                    }
                }
                //搜尋商品名稱並更新資料 再寫回檔案
                wrt_back_file(drinks);
            }
            else if(admin_num==2){
                cout<<"Item name you want to change:";
                string tmp;
                int new_stoke;
                cin>>tmp;
                cout<<"new Item stoke you want:";
                cin>>new_stoke;
                for(auto &t:drinks){
                    if(t.drink_name==tmp){
                        t.stock=new_stoke;
                    }
                }
                //搜尋商品名稱並更新資料 再寫回檔案

                wrt_back_file(drinks);
            }
            else if(admin_num==3){
                sort(rec.begin(),rec.end(),cmp);
                cout<<"Sales volume:"<<endl;
                for(int i=0;i<rec.size();++i){
                    cout<<rec[i].first<<" "<<rec[i].second<<endl;
                }
                cout<<endl;
                cout<<"Profit: "<<total_sum<<endl<<endl;
                continue;
            }
            else{
                continue;
            }
        }
        else{
            continue; // type false number
        }
    }
}



