#include "Lynton.h"
#include "Lynton/Core/EntryPoint.h">"

#include "EditorLayer.h"

namespace Lynton
{

    class Lynmouth : public Application
    {
    public:
		Lynmouth()
		    : Application("Lynmouth")
	    {
		    push_layer(new EditorLayer());
	    }

	    ~Lynmouth()
	    {
		    
	    }
    };

    Application* create_application()
    {
	    return new Lynmouth();
    }
    
}
