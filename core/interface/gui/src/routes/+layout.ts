export const prerender = true;
export const ssr = false;

import { register, init, getLocaleFromNavigator } from 'svelte-i18n';

register('en', () => import('$lib/lang/en.json'));

init({
    fallbackLocale: 'en',
    initialLocale: getLocaleFromNavigator(),
});