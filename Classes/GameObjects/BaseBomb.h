//
//  BaseBomb.h
//  gamebase
//
//  Created by NGOCDIEP on 6/30/15.
//
//

#ifndef __gamebase__BaseBomb__
#define __gamebase__BaseBomb__

#include <DroppingObject.h>


class BaseBomb : public DroppingObject
{
public:
    
    void onDestroyObject() override;
    
private:
    
protected:
    AnimationKey _boomKey;
};

#endif /* defined(__gamebase__BaseBomb__) */
