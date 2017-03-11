#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#define INFINITY 999
using namespace std;

//********************************************************************************************
                                        //DIJIKSTRA
//********************************************************************************************

class Move{
    public:
        int fromWhere;
        int toWhere;
        int howManyToSend;
        bool isDone;
        int owner;
        Move(int a, int b,int c, int d){
            fromWhere = a;
            toWhere = b;
            howManyToSend = c;
            isDone = false;
            owner = d;
        }
};
vector <Move> AllMoves;

class Dijkstra{

    public:
        int predecessor[16];
        int adjMatrix[16][16]; //RECZNIE
        int distance[16];
        bool mark[16];
        int source; //RECZNIE
        int numOfVertices;
        void initialize(){
            for(int i=0;i<numOfVertices;i++) {
                mark[i] = false;
                predecessor[i] = -1;
                distance[i] = INFINITY;
            }
            distance[source]= 0;
        }
        int getClosestUnmarkedNode(){
                int minDistance = INFINITY;
                int closestUnmarkedNode;
                for(int i=0;i<numOfVertices;i++) {
                if((!mark[i]) && ( minDistance >= distance[i])) {
                    minDistance = distance[i];
                    closestUnmarkedNode = i;
                }
                }
                return closestUnmarkedNode;
        }
        void calculateDistance(){
            initialize();
            int minDistance = INFINITY;
            int closestUnmarkedNode;
            int count = 0;
            while(count < numOfVertices) {
                closestUnmarkedNode = getClosestUnmarkedNode();
                mark[closestUnmarkedNode] = true;
                for(int i=0;i<numOfVertices;i++) {
                    if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i]>0) ) {
                        if(distance[i] > distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i]) {
                            distance[i] = distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i];
                            predecessor[i] = closestUnmarkedNode;
                        }
                    }
                }
                count++;
            }
        }
        void printPath(int node, int howMany, int owner){
            vector<int> stackk;
            vector<int> moves;
            stackk.push_back(node);
            moves.push_back(node);
            while(!stackk.empty())
            {
                node = predecessor[node];
                stackk.pop_back();
                if(node == source){
                    moves.push_back(node);
                    break;
                } else {
                    stackk.push_back(node);
                    moves.push_back(node);
                }



            }
            for(int i = 0; i < moves.size() - 1; i++){
                Move temp(moves.at(i + 1), moves.at(i), howMany, owner);
                AllMoves.push_back(temp);
            }


            /*
            if(node == source){
                //cerr<<node<<" ";



            }
            else {
                printPath(predecessor[node]);
               //cerr<<node<<" ";

            }*/
        }
};

vector <Dijkstra> dijikstras;


//********************************************************************************************
                                        //CLASSES
//********************************************************************************************

class Prediction{
public:
    int factoryID;
    int income;
    int howManyToSend;
    Prediction(int _factoryID,int _income,int _howManyToSend){
        factoryID = _factoryID;
        income = _income;
        howManyToSend = _howManyToSend;
    }

};


class Factory{
public:
    int id;
    int owner;
    int cyborgsInside;
    int factoryProduction;
    int status;
    bool frontEnd;
    int produceAgain;

    Factory(int _id, int _owner, int _cyborgsInside, int _factoryProduction, int _produceAgain){
     id = _id;
     owner = _owner;
     cyborgsInside = _cyborgsInside;
     factoryProduction = _factoryProduction;
     frontEnd = false;
     produceAgain = _produceAgain;
    }

    void sendCyborgs(int whereToSend, int numberOfCyborgs, int owner){
       // cout << ";MOVE " << id << " " << whereToSend << " " << numberOfCyborgs;
        dijikstras.at(id).printPath(whereToSend, numberOfCyborgs, owner);
    }

    void sendAllCyborgs(int whereToSend,int owner){
      //  cout << ";MOVE " << id << " " << whereToSend << " " << cyborgsInside;
        dijikstras.at(id).printPath(whereToSend, cyborgsInside, owner);
    }

};

class Troop{
public:
    int id;
    int owner;
    int whereTroopIs;
    int whereTroopGoes;
    int cyborgsInside;
    int turnsToReach;

    Troop(int _id, int _owner, int _whereTroopIs, int _whereTroopGoes, int _cyborgsInside, int _turnsToReach){
        id = _id;
        owner = _owner;
        whereTroopIs = _whereTroopIs;
        whereTroopGoes = _whereTroopGoes;
        cyborgsInside = _cyborgsInside;
        turnsToReach = _turnsToReach;
    }

    void sendCyborgs(int whereToSend, int numberOfCyborgs){
        //cout << ";MOVE " << whereTroopIs << " " << whereToSend << " " << numberOfCyborgs << endl;
    }
   void sendAllCyborgs(int whereToSend){
        //cout << ";MOVE " << whereTroopIs << " " << whereToSend << " " << cyborgsInside << endl;
    }
};




//********************************************************************************************
                                        //VARIABLES
//********************************************************************************************

vector <Factory> AllFactories;
vector <Troop> AllTroops;

vector <Factory> MyFactories;
vector <Troop> MyTroops;

vector <Factory> EnemyFactories;
vector <Troop> EnemyTroops;

vector<Factory> NeutralFactories;
vector <Factory> NotMy;

vector <Factory> FrontFactories;
int tura = 0;
bool firstBomb = false;

int change(int x){
    for(int c =0; c < AllFactories.size(); c++){
        if(AllFactories.at(c).id == x){
            return c;
        }
        if(c == AllFactories.size() - 1){
            return -1;
        }
    }

}



int main()
{
    int factoryCount; // the number of factories


    cin >> factoryCount; cin.ignore();

    int factoryLinks[factoryCount][factoryCount];
    for(int i = 0; i < factoryCount; i++)
    {
        for(int j = 0; j < factoryCount; j++){
            factoryLinks[i][j] = -1;
        }
    }



    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory1 >> factory2 >> distance; cin.ignore();
        factoryLinks[factory1][factory2] = distance;
        factoryLinks[factory2][factory1] = distance;
    }

    // GAME LOOP

    for(int i = 0;i < factoryCount; i++){
        Dijkstra temp;
        temp.numOfVertices = factoryCount;
        temp.source = i;
        for(int j = 0; j < factoryCount; j++){
            for(int k = 0; k < factoryCount; k++){
                if(j != k)
                temp.adjMatrix[j][k] = factoryLinks[j][k];
            }
        }
        temp.calculateDistance();
        dijikstras.push_back(temp);
    }





        bool firstBomb = false;
    while (1) {

        tura++;
        AllFactories.clear();
        AllTroops.clear();

        MyFactories.clear();
        MyTroops.clear();

        EnemyFactories.clear();
        EnemyTroops.clear();

        NeutralFactories.clear();
        NotMy.clear();

        int entityCount; // the number of entities (e.g. factories and troops)
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();

            if(entityType == "FACTORY")
            {
                Factory tempFactory(entityId, arg1, arg2, arg3, arg4);
                AllFactories.push_back(tempFactory);
                if(arg1 == 1){
                    MyFactories.push_back(tempFactory);
                } else if(arg1 == -1) {
                    EnemyFactories.push_back(tempFactory);
                    NotMy.push_back(tempFactory);
                } else if(arg1 == 0){
                    NeutralFactories.push_back(tempFactory);
                    NotMy.push_back(tempFactory);
                }

            } else if(entityType == "TROOP")
            {
                Troop tempTroop(entityId, arg1, arg2, arg3, arg4, arg5);
                AllTroops.push_back(tempTroop);
                if(arg1 == 1){
                    MyTroops.push_back(tempTroop);
                } else {
                    EnemyTroops.push_back(tempTroop);
                }
            }
        }


for(int i = 0; i < MyFactories.size(); i++){
    for(int j = 0; j < MyTroops.size(); j++){
        if(MyFactories.at(i).id == MyTroops.at(j).whereTroopGoes){
            MyFactories.at(i).cyborgsInside += MyTroops.at(j).cyborgsInside;
            MyTroops.at(j).cyborgsInside = 0;
        }
    }
}
//Adding my Troops
for(int i = 0; i < NeutralFactories.size(); i++){
    int myCount = 0;
    int enemyCount = 0;

    for(int j = 0; j < AllTroops.size(); j++){
        if(AllTroops.at(j).whereTroopGoes == NeutralFactories.at(i).id)
        {
            if(AllTroops.at(j).owner == 1){
                myCount += AllTroops.at(j).cyborgsInside;
            } else if(AllTroops.at(j).owner == -1){
                enemyCount += AllTroops.at(j).cyborgsInside;
            }
        }

    }
     if(myCount > enemyCount + NeutralFactories.at(i).cyborgsInside){
            NeutralFactories.at(i).status = 2;
        } else {
             NeutralFactories.at(i).status = 3;
        }

}
//ADDING ENEMIES TO THEIR BASE
for(int i = 0; i < EnemyFactories.size(); i++){
    for(int j = 0;j< EnemyTroops.size(); j++){
        if(EnemyFactories.at(i).id == EnemyTroops.at(j).whereTroopGoes){

            EnemyFactories.at(i).cyborgsInside +=  EnemyTroops.at(j).cyborgsInside;
            EnemyTroops.at(j).cyborgsInside = 0;
        }

    }

}

//COUNTING MY ALL TROOPPS
int allMy = 0;
for(int i = 0; i < MyFactories.size(); i++)
{
    allMy += MyFactories.at(i).cyborgsInside;
}

for(int i = 0; i < MyTroops.size(); i++){
    allMy += MyTroops.at(i).cyborgsInside;
}

int allEnemy = 0;
for(int i = 0; i < EnemyFactories.size(); i++)
{
    allEnemy += EnemyFactories.at(i).cyborgsInside;
}

for(int i = 0; i < EnemyTroops.size(); i++)
{
    allEnemy += EnemyTroops.at(i).cyborgsInside;
}

//FINDING LARTGEST DISTANCE
int largest = 0;
for(int i = 0;i < AllFactories.size(); i++){
    for(int j = 0;j < AllFactories.size(); j++){
        if(largest < factoryLinks[AllFactories.at(i).id][AllFactories.at(j).id]){
            largest = factoryLinks[AllFactories.at(i).id][AllFactories.at(j).id];
        }

    }

}

int myProduction = 0;
for(int i = 0; i < MyFactories.size(); i++){

    myProduction += MyFactories.at(i).factoryProduction;
}

int enemyProduction = 0;
for(int i = 0; i < EnemyFactories.size(); i++){

    enemyProduction += EnemyFactories.at(i).factoryProduction;
}



//********************************************************************************************
                                        //ACTIONS
//********************************************************************************************

cout << "MSG " << "MY: " << myProduction << " ENEMY: " << enemyProduction;

                //********************************************************************************************
                                                        //DEFED
                //********************************************************************************************
                int closest = INFINITY;
                int closestId = 0;

                for(int i = 0; i < MyFactories.size(); i++)
                {
                    //IF IS SOMETHING TO DEF
                    int enemies = 0;
                    for(int j = 0; j < EnemyTroops.size(); j++){
                        if(EnemyTroops.at(j).whereTroopGoes == MyFactories.at(i).id){
                            enemies+=EnemyTroops.at(j).cyborgsInside;
                        }
                        if(EnemyTroops.at(j).turnsToReach < closest){
                            closest = EnemyTroops.at(j).turnsToReach;
                            closestId = j;
                        }
                    }
                    if(MyFactories.at(i).cyborgsInside < enemies){
                        MyFactories.at(i).status = 1;
                        int howMany = enemies - MyFactories.at(i).cyborgsInside - ((closest - MyFactories.at(i).produceAgain) * MyFactories.at(i).factoryProduction);
                        int howSent = 0;
                        for(int c = 0; c < MyFactories.size(); c++){
                            if(MyFactories.at(c).id != MyFactories.at(i).id){
                                if(MyFactories.at(c).status == 0)
                                {
                                    if(howSent < howMany){
                                        MyFactories.at(c).sendCyborgs(MyFactories.at(i).id, MyFactories.at(c).cyborgsInside / 3, 1);
                                        howSent = MyFactories.at(c).cyborgsInside / 3;
                                    }
                                }
                            }
                        }
                    } else {
                        MyFactories.at(i).status = 0;
                    }
                }


                //********************************************************************************************
                                                        //TAKING NEUTRAL FACTORIES
                //********************************************************************************************
                //COUTNING WHO HAS CLOSER
                for(int i = 0; i < NeutralFactories.size(); i++){
                    for(int j = 0; j < MyFactories.size(); j++) {
                        if(factoryLinks[NeutralFactories.at(i).id][MyFactories.at(j).id] < largest / 2){
                            if(MyFactories.at(j).status == 0)
                            MyFactories.at(j).sendCyborgs(NeutralFactories.at(i).id, NeutralFactories.at(i).cyborgsInside + 1, 0);
                        }
                    }
                }

                //********************************************************************************************
                                                        //INCREASING PRODUCTION
                //********************************************************************************************
                 for(int i = 0; i < MyFactories.size(); i++)
                {
                    if(MyFactories.at(i).factoryProduction <= 3){
                        if(MyFactories.at(i).status == 0){
                            if(MyFactories.at(i).cyborgsInside > 10){
                                if(MyFactories.at(i).frontEnd == false)
                                    if(myProduction < enemyProduction)
                                        cout << ";INC " << MyFactories.at(i).id;
                            }
                        }
                    }
                }

                //********************************************************************************************
                                                        //BOMB SENDING
                //********************************************************************************************

                int prod = 0;
                int prodId = 0;
                for(int i = 0; i < EnemyFactories.size(); i++){
                    if(EnemyFactories.at(i).factoryProduction > prod){
                        prod = EnemyFactories.at(i).factoryProduction;
                        prodId = i;
                    }
                }
                if((MyFactories.size() > 0) && (firstBomb == false) && (tura > 5)){
                    cout << ";BOMB " << MyFactories.at(0).id << " " << EnemyFactories.at(prodId).id;
                    firstBomb = true;
                } else if((firstBomb==true) && (tura > 20)){
                    if(MyFactories.size()  >0)
                        if(EnemyFactories.size() > 0)
                    cout << ";BOMB " << MyFactories.at(0).id << " " << EnemyFactories.at(prodId).id;

                }


                //********************************************************************************************
                                                    //ENEMY ATACK
                //********************************************************************************************
            int defending = 0;
            for(int i = 0; i < MyFactories.size(); i++){
                if(MyFactories.at(i).status == 1){
                    defending++;
                }
            }
            for(int i = 0;i < MyFactories.size(); i++)
            {
                for(int j = 0; j < EnemyFactories.size(); j++){

                    if(factoryLinks[MyFactories.at(i).id][EnemyFactories.at(j).id] <= largest / 3){
                        int income = EnemyFactories.at(j).cyborgsInside + (factoryLinks[MyFactories.at(i).id][EnemyFactories.at(j).id] * EnemyFactories.at(j).factoryProduction) ;
                        cerr << EnemyFactories.at(j).id << " Income: " << income;
                        if(MyFactories.at(i).cyborgsInside > income){
                            if(MyFactories.at(i).status == 0 )
                                if(defending<= MyFactories.size() / 2)
                                    MyFactories.at(i).sendCyborgs(EnemyFactories.at(j).id,income + 1, -1);
                        }
                    }
                }
            }
                //********************************************************************************************
                                                        //FINDING FRONT
                //********************************************************************************************

            for(int i = 0; i < EnemyFactories.size(); i++)
            {
                int closestMy = 999;
                int closestMyId = 0;
                for(int j = 0; j < MyFactories.size(); j++){
                    if(factoryLinks[MyFactories.at(j).id][EnemyFactories.at(i).id] < closestMy){
                        closestMy = factoryLinks[MyFactories.at(j).id][EnemyFactories.at(i).id];
                        closestMyId = j;
                    }
                }
                if(MyFactories.size() > 0)
                    MyFactories.at(closestMyId).frontEnd = true;
            }
            //DEBUG
            int countt = 0;
            for(int i = 0; i < MyFactories.size(); i++){
                if(MyFactories.at(i).frontEnd == true)
                    countt++;
            }
            cerr << countt << endl;
                //********************************************************************************************
                                                        //SENDING TO FRONT
                //********************************************************************************************

            for(int i = 0; i < MyFactories.size(); i++){
                if(MyFactories.at(i).frontEnd == true){
                    for(int j = 0; j < MyFactories.size(); j++){
                        if(i != j){
                            if( MyFactories.at(j).status == 0)
                                MyFactories.at(j).sendCyborgs(MyFactories.at(i).id, MyFactories.at(j).cyborgsInside / 2, 1);
                        }
                    }
                }
            }

                //********************************************************************************************
                                                        //DOING COMMANDS
                //********************************************************************************************


            int howManyDelete = 0;
            for(int i = 0; i < AllMoves.size(); i++){
                int newId = change(AllMoves.at(i).fromWhere);
                int check = change(AllMoves.at(i).toWhere);
                if(newId != -1){

                    if(AllFactories.at(newId).owner == 1){
                        if(AllFactories.at(newId).cyborgsInside >= AllMoves.at(i).howManyToSend){
                            if(AllMoves.at(i).owner == AllFactories.at(check).owner)
                            {
                                cout << ";MOVE " << AllMoves.at(i).fromWhere << " " << AllMoves.at(i).toWhere << " " << AllMoves.at(i).howManyToSend;
                                howManyDelete++;
                                AllMoves.at(i).isDone = true;
                            } else {
                                howManyDelete++;
                                AllMoves.at(i).isDone = true;
                            }
                        }
                    }

                }
            }

            int indeks = 0;
            while(howManyDelete > 0){
                if(AllMoves.at(indeks).isDone == true){
                    AllMoves.erase(AllMoves.begin() + indeks);
                    howManyDelete--;
                    indeks--;
                }
                indeks++;

            }

             cout << ";WAIT"<<endl;




        }


    } //MAIN FINISH
