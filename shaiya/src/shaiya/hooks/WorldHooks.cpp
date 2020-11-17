#include <shaiya/World.hpp>
#include <shaiya/hooks/command/CommandManager.hpp>
#include <shaiya/utils/Hook.hpp>

/**
 * The address for parsing a console command
 */
constexpr auto SConsoleParseCommand = 0x04F6293;

/**
 * The address to return to for an unsuccessfully handled command.
 */
constexpr auto SConsoleParseCommandReturn = 0x04F6299;

/**
 * The address to return to for a successful command.
 */
constexpr auto SConsoleParseCommandExit = 0x04F6314;

/**
 * Hook the parsing of console commands.
 */
void __declspec(naked) SConsoleHook()
{
    __asm {
        push ebp
        mov ebp,esp

        push edx
        push ebx
        call CommandManager::execute
        add esp,8
        test eax,eax

        mov esp,ebp
        pop ebp

        jne handled
        jmp unhandled

        handled:
            mov ecx,edx
            jmp SConsoleParseCommandExit

        unhandled:
            mov ecx,[esi+0x54]
            mov eax,[ecx+0x04]
            jmp SConsoleParseCommandReturn
    }
}

/**
 * Initialises the game world hooks.
 */
template<>
void World::hook<HookType::World>(const toml::table& config)
{
    CommandManager::init();

    LOG(INFO) << "Init world hooks";
    memory(SConsoleParseCommand, 6, (DWORD)SConsoleHook);
}