#ifndef ISEARCH_H
#define ISEARCH_H
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <list>
#include <math.h>
#include <unordered_map>

class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);

        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);

    protected:
        Node findMin();
        virtual void addOpen(Node newNode, const Map &map);
        virtual void addFocal(FocalElem elem, const Map &map);
        virtual void eraseFocal(FocalElem elem);
        virtual void updateFocal(const Map &map);
        virtual double computeHFromCellToCell(int start_i, int start_j, int fin_i, int fin_j, const EnvironmentOptions &options) = 0;
        virtual std::list<Node> findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options);
        virtual void makePrimaryPath(Node curNode);//Makes path using back pointers
        virtual void makeSecondaryPath();//Makes another type of path(sections or points)
        virtual Node resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options) {return current;}//Function for Theta*
        virtual bool stopCriterion();
        virtual void printLists();

        SearchResult                    sresult;
        std::list<Node>                 lppath, hppath;
        std::unordered_map<int,Node>    close;
        std::vector<std::list<Node>>    open;
        std::list<FocalElem>            focal;
        std::list<FocalElem>            overbounded_elements;
        double                          fmin;
        double                          focal_weight;
        int                             openSize;
        double                          hweight;//weight of h-value
        bool                            breakingties;//flag that sets the priority of nodes in addOpen function when their F-values is equal

};
#endif
