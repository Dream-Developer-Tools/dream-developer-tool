<script>
    import Navbar from "$lib/components/Navbar.svelte";
    import ClarityPluginLine from '~icons/clarity/plugin-line';
    import {writable} from "svelte/store";
    import {navbarPosition} from "$lib/config.ts";

    let toolPath = writable("Tools");
</script>

<div class="{$navbarPosition === 'lside'? 'flex' : ''}">
    <Navbar />

    <!-- add clases based on an if statement-->
    <div class="{$navbarPosition === 'lside'? 'vert-navbar' : ''}">
        <div style="height: 75vh" class="card w-3/4 m-auto mt-6 scroll-auto">
            <ol id="breadcrumb" class="breadcrumb pl-2 pt-2">
                {#each {length: $toolPath.split("/").length - 1} as _,i}
                    <li on:click={() => toolPath.set($toolPath.split("/").slice(0, i + 1).join("/"))}
                        class="pl-2 text-2xl crumb hover:cursor-pointer">{$toolPath.split("/")[i]}</li>
                    <li class="pl-2 text-2xl crumb-separator">\</li>
                {/each}
                <li class="pl-2 text-2xl crumb">{$toolPath.split("/")[$toolPath.split("/").length - 1]}</li>
            </ol>
            <hr class="my-3 !border-t-2" />
            <div style="width: 97%" class="mx-auto">
                <nav class="mx-auto input-group list-nav rounded w-11/12">
                    <label class="text-lg p-2">Tools</label>
                    <ul>
                        <li>
                            <button>
                                <span class="badge bg-primary-500"><ClarityPluginLine /></span>
                                <span class="flex-auto w-min">Skeleton</span>
                            </button>
                        </li>
                    </ul>
                </nav>
            </div>
        </div>
    </div>
</div>