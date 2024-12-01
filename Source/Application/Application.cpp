#include <pch.h>

Actor PlayerActor = 0;
Actor TargetActor = 0;
bool nolasso = true;

void Application::Initialize(HMODULE _Module)
{
    InputsManager::Register();


    ScriptRegister(_Module, []
        {
            while (true)
            {
                PlayerActor = UNSORTED::GET_PLAYER_ACTOR(0);
                if (nolasso)
                {
                    TargetActor = UNSORTED::GET_LASSO_TARGET(PlayerActor);
                    if (!UNSORTED::IS_ACTOR_HUMAN(TargetActor))
                    {
                        TargetActor = 0;
                    }
                    else if (TargetActor)
                    {
                        nolasso = false;
                    }
                }
                if (UNSORTED::GET_MOUNT(PlayerActor) && TargetActor)
                {
                    UNSORTED::ACTOR_PUT_WEAPON_IN_HAND(PlayerActor, WEAPON_LASSO_Lasso, true);
                    UNSORTED::IMMEDIATELY_LASSO_TARGET(PlayerActor, TargetActor, 0);
                }
                if (!HEALTH::IS_ACTOR_ALIVE(TargetActor) || Input::IsKeyJustPressed(KEY_F))
                {
                    UNSORTED::DETACH_LASSO(TargetActor);
                    nolasso = true;
                    TargetActor = 0;
                }
                if (!UNSORTED::GET_MOUNT(PlayerActor))
                {
                    nolasso = true;
                    TargetActor = 0;
                }

                BUILTIN::WAIT(0);
            }
    });
}


void Application::Shutdown(HMODULE _Module)
{
    ScriptUnregister(_Module);
		
    InputsManager::Unregister();
}
