import { writable } from 'svelte/store';
import {Page} from "$lib/types";



const page = writable(Page.HOME);

export { page };