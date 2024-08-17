<script>
    import Navbar from "$lib/components/Navbar.svelte";
    import {navbarPosition} from "$lib/config";

</script>

<div class="{$navbarPosition === 'lside'? 'flex' : ''}">
    <Navbar />

    <!-- add clases based on an if statement-->
    <div class="{$navbarPosition === 'lside'? 'vert-navbar' : ''}">
    </div>
</div>
