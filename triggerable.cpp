#include "triggerable.h"

Triggerable::Triggerable()
{
    triggered       = false;
    triggerableList    = TriggerableList::getInstance();
}

Triggerable::~Triggerable()
{
    triggerableList->removeTriggerable( triggerableName );
    triggerableList->release();
}

void Triggerable::init( string triggerableName )
{
    triggerableList->insertTriggerable( triggerableName, this );
    this->triggerableName = triggerableName;
}
