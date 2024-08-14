<script lang="ts">
    import MaterialSymbolsList from '~icons/material-symbols/list';

    import {writable, type Writable} from "svelte/store";

    export let settingsPath: Writable<string>;
    export let onNavigate: (subPath: string) => () => void;
    import { configStore } from "$lib/config";
    let currentConfig = [];
    settingsPath.subscribe((value) => {
        let path = value.split('/');
        let conf = $configStore;
        for (let i = 1; i < path.length; i++) {
            // find the item in the currentConfig that matches the current path
            let item = conf.find((item) => item.name === path[i]);
            if (!item) {
                // if the item is not found, set the currentConfig to an empty array
                currentConfig = [];
                break;
            }
            conf = item.children;
        }
        currentConfig = conf;
    });

    function updateConfig(name: string, value: any) {
        let path = $settingsPath.split('/');
        let conf = $configStore;
        for (let i = 1; i < path.length; i++) {
            let item = conf.find((item) => item.name === path[i]);
            if (!item) {
                currentConfig = [];
                break;
            }
            conf = item.children;
        }
        let item = conf.find((item) => item.name === name);
        item.value = value;
        $configStore = $configStore;
    }
</script>

<!--Loop through the currentConfig-->

<div style="width: 97%" class="mx-auto">
    {#if currentConfig.find((item) => item.type === "section")}
        <nav class="input-group list-nav rounded w-1/2">
            <!-- (optionally you can provide a label here) -->
            <label class="text-lg p-2">Sub-menus</label>
            <ul>
                {#each currentConfig as item}
                    {#if item.type === "section"}
                        <li>
                            <button on:click={onNavigate(item.name)} class="flex items-center p-2 hover:bg-gray-100">
                                <span class="badge bg-primary-500"><MaterialSymbolsList class="text-sm"/></span>
                                <span class="flex-auto">{item.name}</span>
                            </button>
                        </li>
                    {/if}
                {/each}

            </ul>
        </nav>
    {/if}

    {#each currentConfig as item}
        {#if item.type !== "section"}
            {#if item.type === "select"}
                <h1 class="mt-3 text-xl">{item.name}</h1>
                <select class="select w-1/2  mr-5" bind:value={item.value} on:change={() => updateConfig(item.name, item.value)}>
                    {#each Object.entries(item.options) as [displayName, value]}
                        <option value={value} selected={value === item.value}>{displayName}</option>
                    {/each}
                </select>
            {/if}
            {#if item.type === "bool"}
                <label class="mt-3 flex items-center space-x-2">
                    {#if item.value}
                        <input class="checkbox" type="checkbox" checked on:change={() => updateConfig(item.name, !item.value)} />
                    {:else}
                        <input class="checkbox" type="checkbox" on:change={() => updateConfig(item.name, !item.value)} />
                    {/if}
                    <p>{item.name}</p>
                </label>
            {/if}
            <hr class="my-3 !border-t-1" />
        {/if}
    {/each}
</div>


