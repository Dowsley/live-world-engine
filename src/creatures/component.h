#ifndef COMPONENT_H
#define COMPONENT_H

struct IComponentRef { virtual Component *create() = 0; };
template< typename T > struct ComponentRef : public IComponentRef {
   virtual T *create( ) {
      return new T();
   }
};

class Component {
   
};

#endif
