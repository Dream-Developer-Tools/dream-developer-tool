<script lang="ts">
    import {AppBar, AppRail, AppRailAnchor, AppRailTile} from '@skeletonlabs/skeleton';
    import { _ } from 'svelte-i18n'
    import MaterialSymbolsHome from '~icons/material-symbols/home';
    import IconamoonDiscover from '~icons/iconamoon/discover';
    import MaterialSymbolsSettings from '~icons/material-symbols/settings';
    import MaterialSymbolsListAltOutline from '~icons/material-symbols/list-alt-outline';
    import MdiTools from '~icons/mdi/tools';
    import { page } from "$lib/state";
    import {Page} from "$lib/types";
    import { goto } from '$app/navigation';
    import {showTextInNavbar, navbarPosition} from "$lib/config";

    let currentTile: number = 0;
</script>

{#if $navbarPosition === 'top'}
    <AppBar gridColumns="grid-cols-3" slotDefault="place-self-center" slotTrail="place-content-end">
        <svelte:fragment slot="lead">
            <div class="flex-row flex">
                <button class="mt-1 inline-block h-max" class:active={$page === Page.HOME} on:click={() => {page.set(Page.HOME); goto("/")}}>
                    <MaterialSymbolsHome class="text-3xl inline-block align-middle" />
                    {#if $showTextInNavbar === true}
                        <div class="text-2xl inline-block align-middle">{$_('page.navbar.home', { default: 'Home' })}</div>
                    {/if}
                </button>
                <button class="mt-1 ml-5 inline-block h-max" class:active={$page === Page.DISCOVER} on:click={() => {page.set(Page.DISCOVER); goto("/discover")}}>
                    <IconamoonDiscover class="text-3xl inline-block align-middle" />
                    {#if $showTextInNavbar === true}
                        <div class="text-2xl inline-block align-middle">{$_('page.navbar.discover', { default: 'Discover' })}</div>
                    {/if}
                </button>
                <button class="mt-1 ml-5 inline-block h-max" class:active={$page === Page.LIST} on:click={() => {page.set(Page.LIST); goto("/list")}}>
                    <MaterialSymbolsListAltOutline class="text-3xl inline-block align-middle" />
                    {#if $showTextInNavbar === true}
                        <div class="text-2xl inline-block align-middle">{$_('page.navbar.list', { default: 'Plugins' })}</div>
                    {/if}
                </button>
                <button class="mt-1 ml-5 inline-block h-max" class:active={$page === Page.TOOLS} on:click={() => {page.set(Page.TOOLS); goto("/tools")}}>
                    <MdiTools class="text-3xl inline-block align-middle" />
                    {#if $showTextInNavbar === true}
                        <div class="text-2xl inline-block align-middle">{$_('page.navbar.tools', { default: 'Tools' })}</div>
                    {/if}
                </button>
                <style>
                    button.active {
                        @apply text-primary-500;
                        transition: all 0.3s ease;
                    }
                </style>
            </div>
        </svelte:fragment>
        <h class="text-3xl font-bold">{$_('page.navbar.title', { default: 'Dream Developer Tool' })}</h>
        <svelte:fragment slot="trail">
            <button class="text-3xl font-bold" on:click={() => {page.set(Page.SETTINGS); goto("/settings")}} class:active={$page === Page.SETTINGS}>
                <MaterialSymbolsSettings />
            </button>
        </svelte:fragment>
    </AppBar>
{:else if $navbarPosition === 'lside'}
    <AppRail class="h-screen">
        <svelte:fragment slot="lead">
            <AppRailAnchor href="/" title="Home">
                <MaterialSymbolsHome class="text-3xl inline-block align-middle" />
            </AppRailAnchor>
            <AppRailAnchor href="/discover" title="Discovery">
                <IconamoonDiscover class="text-3xl inline-block align-middle" />
            </AppRailAnchor>
            <AppRailAnchor href="/list" title="Plugin List">
                <MaterialSymbolsListAltOutline class="text-3xl inline-block align-middle" />
            </AppRailAnchor>
            <AppRailAnchor href="/tools" title="Tools">
                <MdiTools class="text-3xl inline-block align-middle" />
            </AppRailAnchor>
        </svelte:fragment>
        <svelte:fragment slot="trail">
            <AppRailAnchor href="/settings" title="Settings">
                <MaterialSymbolsSettings class="text-3xl inline-block align-middle" />
            </AppRailAnchor>
        </svelte:fragment>
    </AppRail>
{/if}