#include <iostream>
#include <vector>
#include <map>
using namespace std;


typedef vector<int> PrefList;
typedef map<int, PrefList> PrefMap;
typedef multimap<int, int> Matching;


map<int, int> CHcapacity ={{1,1},{2,1},{3,1}};
PrefMap PrefCHLists = {{1,{5,4,6}},{2,{4,6,5}},{3,{4,5,6}}};
PrefMap PrefONLists = {{4,{2,1,3}},{5,{3,1,2}},{6,{1,3,2}}};

Matching RVV(Matching Mz);
Matching foundBP(Matching m, PrefMap fPrefCHLists, PrefMap fPrefONLists);
bool add(int a, int r, map<int, int> &S, Matching &m);
Matching blockingAgent(int agent, map<int, int> S, Matching m);
void satisfy(int CH, int ON, map<int, int> &S, Matching &m );

int main()
{
    Matching match={{1,4},{2,5},{3,6}};
    Matching final=RVV(match);
    for( Matching::iterator it = final.begin(); it != final.end(); it++ ){
        cout<<it->first<<"->"<<it->second<<"\n";
    }
    return 0;
}

Matching RVV(Matching Mz){
    Matching tempM = Mz;
    map<int, int> S;
    Matching bp = foundBP(tempM, PrefCHLists, PrefONLists);
    int t=0;
    while (!bp.empty()) {
        t++;
        bool found = false;
        for(auto const& p : bp){
            const int CH = p.first;
            const int ON = p.second;
            if(S.find(CH)!=S.end() && S.find(ON)==S.end()){
                found = add(ON, 0, S, tempM); //1=CH,0=ON
            }else if(S.find(ON)!=S.end() && S.find(CH)==S.end()){
                found = add(CH, 1, S, tempM); //1=CH,0=ON
            }
        }
        if(!found){
            satisfy(bp.begin()->first,bp.begin()->second, S, tempM);
        }
        bp.clear();
        bp = foundBP(tempM, PrefCHLists, PrefONLists);
    }

    return tempM;
}

Matching foundBP(Matching m, PrefMap fPrefCHLists, PrefMap fPrefONLists){
    Matching BP;
    for(auto const& p : fPrefCHLists){
        const int CH = p.first;
        const PrefList CHpref = p.second;
        pair<Matching::iterator, Matching::iterator> ret;
        ret = m.equal_range(CH);
        PrefList ONmatched;
        for( Matching::iterator it = ret.first; it != ret.second; it++ ){
            ONmatched.push_back(it->second);
        }
        size_t j = 0;
        for( int i = 0; i < CHcapacity[CH]; i++ ){
            if(j < CHpref.size()){
                const int ON = CHpref[j];
                bool found = false;
                for( size_t k = 0; k < ONmatched.size(); k++ ){
                    if( ON == ONmatched[k] ){
                        found=true;
                        break;
                    }
                }
                if(!found){
                    bool insertBP = true;
                    for( Matching::iterator it = m.begin(); it != m.end(); it++ ){
                        if(it->second == ON){
                            const int onCH = it->first;
                            PrefList ONpref = fPrefONLists.find(ON)->second;
                            for(size_t iter = 0; iter < ONpref.size(); iter++){
                                if(ONpref[iter]==CH){
                                    break;
                                }
                                if(ONpref[iter]==onCH){
                                    insertBP = false;
                                    i--;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    if(insertBP){
                        BP.insert(std::pair<int, int>(CH,ON));
                    }
                }
                j++;
            }
        }
    }
    return BP;
}

bool add(int a, int role, map<int, int> &S, Matching &m){
    if(role==0){
        int ON = a;
        for (auto it = m.begin(); it != m.end(); it++){
            if (it->second == ON){
                m.erase(it);
                break;
            }
        }
        S[ON]=1;
        Matching aBps = blockingAgent(ON, S, m);
        while(!aBps.empty()){
            Matching::iterator bestIt = aBps.begin();
            const int inCH = bestIt->first;
            const int inON = bestIt->second;
            if(CHcapacity[inCH]<=m.count(inCH)){
                Matching::iterator worst;
                int iWorst=-1;
                std::pair <Matching::iterator, Matching::iterator> ret;
                ret = m.equal_range(inCH);
                PrefList CHpref = PrefCHLists.find(inCH)->second;
                for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
                    const int tON = it->second;
                    for(size_t jt = 0; jt < CHpref.size(); jt++){
                        if(CHpref[jt] == tON){
                            if(iWorst < jt){
                                iWorst = jt;
                                worst = it;
                                break;
                            }
                        }else if(jt==CHpref.size()-1){
                            iWorst = -1;
                        }
                    }
                    if(iWorst==-1){
                        worst = it;
                        break;
                    }
                }
                ON = worst->second;
                m.erase(worst);
            }
            m.insert(std::pair<int,int>(inCH,inON));
            aBps = blockingAgent(ON, S, m);
        }
    }else{
        int CH = a;
        if(CHcapacity[CH]<=m.count(CH)){
            Matching::iterator worst;
            int iWorst=-1;
            std::pair <Matching::iterator, Matching::iterator> ret;
            ret = m.equal_range(CH);
            PrefList CHpref = PrefCHLists.find(CH)->second;
            for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
                const int tON = it->second;
                for(size_t jt = 0; jt < CHpref.size(); jt++){
                    if(CHpref[jt] == tON){
                        if(iWorst < jt){
                            iWorst = jt;
                            worst = it;
                            break;
                        }
                    }else if(jt==CHpref.size()-1){
                        iWorst = -1;
                    }
                }
                if(iWorst==-1){
                    worst = it;
                    break;
                }
            }
            m.erase(worst);
        }
        S[CH]=1;
        Matching aBps = blockingAgent(CH, S, m);
        while(!aBps.empty()){
            Matching::iterator bestIt = aBps.begin();
            const int inCH = bestIt->first;
            const int inON = bestIt->second;
            for (auto it = m.begin(); it != m.end(); it++){
                if (it->second == inON){
                    CH = it->first;
                    m.erase(it);
                    break;
                }
            }
            m.insert(std::pair<int,int>(inCH,inON));
            aBps = blockingAgent(CH, S, m);
        }
    }
    return true;
}

Matching blockingAgent(int agent, map<int, int> S, Matching m){
    Matching bestbps;
    for (auto it = m.begin(); it != m.end(); it++){
        if (S.find(it->first) == S.end() || S.find(it->second) == S.end()){
            it = m.erase(it);
        }
    }
    PrefMap tempPrefCHLists = PrefCHLists;
    PrefMap tempPrefONLists = PrefONLists;
    PrefMap::iterator tempListit = tempPrefCHLists.begin();
    while (tempListit != tempPrefCHLists.end()){
        if (S.find(tempListit->first) == S.end()){
            tempListit = tempPrefCHLists.erase(tempListit);
        }else{
            PrefList &list = tempListit->second;
            PrefList::iterator jt = list.begin();
            while (jt != list.end()){
                if (S.find(*jt) == S.end()){
                    jt = list.erase(jt);
                }else{
                    ++jt;
                }
            }
            ++tempListit;
        }
    }
    tempListit = tempPrefONLists.begin();
    while (tempListit != tempPrefONLists.end()){
        if (S.find(tempListit->first) == S.end()){
            tempListit = tempPrefONLists.erase(tempListit);
        }else{
            PrefList &list = tempListit->second;
            PrefList::iterator jt = list.begin();
            while (jt != list.end()){
                if (S.find(*jt) == S.end()){
                    jt = list.erase(jt);
                }else{
                    ++jt;
                }
            }
            ++tempListit;
        }
    }
    Matching bpM = foundBP(m, tempPrefCHLists, tempPrefONLists);
    if(!bpM.empty()){
        PrefMap::iterator iter = (PrefCHLists.find(agent)!=PrefCHLists.end())?PrefCHLists.find(agent):PrefONLists.find(agent);
        PrefList list = iter->second;
        for(size_t i=0; i<list.size();i++){
            const int best = list[i];
            for (auto it = bpM.begin(); it != bpM.end(); it++){
                if((it->first==best && it->second==agent) || (it->second==best && it->first==agent)){
                    bestbps.insert(std::pair<int,int>(it->first,it->second));
                    break;
                }
            }
        }
    }
    return bestbps;
}

void satisfy(int CH, int ON, map<int, int> &S, Matching &m ){
    S[ON]=1;
    S[CH]=1;
    for (auto it = m.begin(); it != m.end(); it++){
        if (it->second == ON){
            m.erase(it);
            break;
        }
    }
    if(CHcapacity[CH]<=m.count(CH)){
        Matching::iterator worst;
        int iWorst=-1;
        std::pair <Matching::iterator, Matching::iterator> ret;
        ret = m.equal_range(CH);
        PrefList CHpref = PrefCHLists.find(CH)->second;
        for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
            const int tON = it->second;
            for(size_t jt = 0; jt < CHpref.size(); jt++){
                if(CHpref[jt] == tON){
                    if(iWorst < jt){
                        iWorst = jt;
                        worst = it;
                        break;
                    }
                }else if(jt==CHpref.size()-1){
                    iWorst = -1;
                }
            }
            if(iWorst==-1){
                worst = it;
                break;
            }
        }
        m.erase(worst);
    }
    m.insert(std::pair<int,int>(CH,ON));
}