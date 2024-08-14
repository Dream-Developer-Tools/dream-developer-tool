// See https://kit.svelte.dev/docs/types#app
// for information about these interfaces
// and what to do when importing types
declare namespace App {
	// interface Locals {}
	// interface PageData {}
	// interface Error {}
	// interface Platform {}
}

import { register, init, getLocaleFromNavigator } from 'svelte-i18n';

register('en', () => import('$lib/lang/en.json'));

init({
    fallbackLocale: 'en',
    initialLocale: getLocaleFromNavigator(),
});