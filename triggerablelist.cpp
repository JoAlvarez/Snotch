#include "triggerablelist.h"

TriggerableList* TriggerableList::instance = NULL;
int TriggerableList::referenceCount = 0;

bool TriggerableList::isMapped( string triggerableName )
{
    if( triggerableMap.count( triggerableName ) > 0 )
        return true;
    else
        return false;
}

void TriggerableList::trigger( string triggerableName )
{
    //Check if element exists
    if( !isMapped( triggerableName ) )
        return;
    triggerableMap[ triggerableName ]->trigger();

}

void TriggerableList::unTrigger( string triggerableName )
{
    //Check if element exists
    if( !isMapped( triggerableName ) )
        return;

    triggerableMap[ triggerableName ]->unTrigger();
}

TriggerableList* TriggerableList::getInstance()
{
    if(instance == NULL)
    {
        instance = new TriggerableList;
    }
    ++referenceCount;
    return instance;
}

void TriggerableList::destroy()
{
    triggerableMap.clear();
}

void TriggerableList::release()
{
    if( --referenceCount < 1 )
    {
        destroy();
    }
    if(referenceCount < 0)
        referenceCount = 0;
}

void TriggerableList::insertTriggerable( string triggerableName, Triggerable* address )
{
    //Check if element exists
    if( isMapped( triggerableName ) )
        return;

    triggerableMap[ triggerableName ] = address;
}

void TriggerableList::removeTriggerable( string triggerableName )
{
    //Check if element exists
    if( !isMapped( triggerableName ) )
        return;

    triggerableMap.erase( triggerableName );
}
