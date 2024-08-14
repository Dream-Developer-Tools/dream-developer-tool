<script lang="ts">
    import Navbar from "$lib/components/Navbar.svelte";
    import SettingsView from "./SettingsView.svelte";
    import {type Writable, writable} from "svelte/store";
    import {navbarPosition} from "$lib/config";
    let settingsPath: Writable<string> = writable("Settings");

    function onNavigate(subPath:string) {
        return () => {
            settingsPath.update((path) => `${path}/${subPath}`);
        }
    }


</script>

<div class="{$navbarPosition === 'lside'? 'flex' : ''}">
    <Navbar />

    <!-- add clases based on an if statement-->
    <div class="{$navbarPosition === 'lside'? 'vert-navbar' : ''}">

        <div style="height: 75vh" class="p-0 card w-3/4 m-auto mt-6 scroll-auto">
            <ol id="breadcrumb" class="breadcrumb pl-2 pt-2">
                {#each {length: $settingsPath.split("/").length - 1} as _,i}
                    <li on:click={() => settingsPath.set($settingsPath.split("/").slice(0, i + 1).join("/"))}
                        class="pl-2 text-2xl crumb hover:cursor-pointer">{$settingsPath.split("/")[i]}</li>
                    <li class="pl-2 text-2xl crumb-separator">\</li>
                {/each}
                <li class="pl-2 text-2xl crumb">{$settingsPath.split("/")[$settingsPath.split("/").length - 1]}</li>
            </ol>
            <hr class="my-3 !border-t-2" />
            <div>
                <SettingsView settingsPath={settingsPath} onNavigate={onNavigate} />
            </div>
        </div>
    </div>
</div>