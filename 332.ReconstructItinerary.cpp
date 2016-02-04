/*Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], 
reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. 
Thus, the itinerary must begin with JFK.

Note:

    If there are multiple valid itineraries, you should return the itinerary that has 
    the smallest lexical order when read as a single string. For example, 
    the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
    All airports are represented by three capital letters (IATA code).
    You may assume all tickets may form at least one valid itinerary.

Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].

Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order. 
*/

/*Note: I failed the following test case: 
[["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]
expected answer: ["JFK","NRT","JFK","KUL"]
*/

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;

        int num_tickets = tickets.size();
        
        if (num_tickets == 0){
            return res;
        }
        
        //create adj-list for the figure
        unordered_map< string, list<string> > adj;
        for (int i=0; i<num_tickets; i++){
            //check whether this starting location already exist in the adj
            string startCity = tickets[i].first;
            string endCity = tickets[i].second;
            unordered_map< string, list<string> >::iterator it = adj.find( startCity );
            if (it == adj.end() ){
                list<string> empty;
                adj[startCity] = empty;
                adj[startCity].push_back(endCity);
            }else{
                //this startCity already exist, attach the endCity information;
                //use insert sorting, in order to alway keep the lexical order
                list<string>::iterator insertionPlace = adj[startCity].begin();
                while (insertionPlace != adj[startCity].end() && *insertionPlace < endCity){
                    insertionPlace++;
                }
                //insert the endCity
                adj[startCity].insert(insertionPlace, endCity);
            }
        }
        
        //now the adj is ready, do a traverse starting with JFK
        res.push_back("JFK");
        for (unordered_map< string, list<string> >::iterator it = adj.find("JFK");
            it!=adj.end() && !it->second.empty(); ){
            string endCity = it->second.front();
            it->second.pop_front();
            res.push_back(endCity);
            
            it = adj.find(endCity);
        }
        
        return res;
    }
};
