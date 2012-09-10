#ifndef __TRIGGERABLE_LIST_H__
#define __TRIGGERABLE_LIST_H__

#include "triggerable.h"
#include <map>
#include <string>

using namespace std;

class Triggerable;

class TriggerableList
{
    private:
        static TriggerableList*         instance;
        static int                      referenceCount;

        map< string, Triggerable* >     triggerableMap;
        bool                            isMapped( string triggerableName );
        void                            destroy();
        Triggerable*                    t;

    public:
        static TriggerableList* getInstance();
        void                    trigger( string triggerableName );
        void                    unTrigger( string triggerableName );
        void                    release();
        void                    insertTriggerable( string triggerableName, Triggerable* address );
        void                    removeTriggerable( string triggerableName );
};

#endif
