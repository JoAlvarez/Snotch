#include "trigger.h"

Trigger::Trigger()
{
    triggerableList = TriggerableList::getInstance();
}

Trigger::~Trigger()
{
    triggerableList->release();
}

void Trigger::trigger( string triggerableName )
{
    triggerableList->trigger( triggerableName );
}

void Trigger::unTrigger( string triggerableName )
{
    triggerableList->unTrigger( triggerableName );
}
