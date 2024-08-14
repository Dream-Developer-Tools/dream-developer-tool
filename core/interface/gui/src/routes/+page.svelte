<script lang="ts">
    import Navbar from "$lib/components/Navbar.svelte";

    import { _ } from 'svelte-i18n';
    import {navbarPosition} from "$lib/config";
    let contributors: { username: string, avatar: string, profile: string }[] = [];
    fetch('https://api.github.com/repos/Dream-Developer-Tools/dream-developer-tool/contributors?per_page=10&anon=true')
        .then(response => response.json())
        .then(data => {
            // only add the login key as username, avatar_url as avatar
            data.forEach((contributor: { login: string, avatar_url: string, html_url: string }) => {
                contributors = [...contributors, { username: contributor.login, avatar: contributor.avatar_url, profile: contributor.html_url }];
            })
        })
        .catch(error => {
            console.error('Error:', error);
        });
</script>


<div class="{$navbarPosition === 'lside'? 'flex' : ''}">
    <Navbar />

    <!-- add clases based on an if statement-->
    <div class="{$navbarPosition === 'lside'? 'vert-navbar' : ''}">
        <div id="contributors">
            <h1 class="px-4 py-3 text-2xl">{$_('page.home.contributors', { default: 'Contributors' })}</h1>
            <div class="snap-x scroll-px-4 snap-mandatory scroll-smooth flex gap-4 overflow-x-auto px-4 py-2">
                <!--    Get contributors from github -->
                {#each contributors as contributor}
                    <button class="snap-start card py-5 w-40 text-center" on:click={() => window.open(contributor.profile, '_blank')}>
                        <img class="w-10 h-10 rounded-full mx-auto" src={contributor.avatar} alt={contributor.username} />
                        <span class="text-lg font-semibold" >{contributor.username}</span>
                    </button>
                {/each}
            </div>
        </div>
    </div>
</div>

