import {writable} from "svelte/store";


const baseConfig: any[] = [
    {
        name: 'Graphical User Interface',
        type: 'section',
        children: [
            {
                name: 'Appearance',
                type: 'section',
                children: [
                    {
                        name: 'Theme',
                        type: 'select',
                        options: {"Dark": "dark", "Light": "light"},
                        value: 'dark'
                    },
                    {
                        name: 'Show text in navbar',
                        type: 'bool',
                        value: true
                    },
                    {
                        name: 'Navbar position',
                        type: 'select',
                        options: {"Top": "top", "Left Side": "lside"},
                        value: 'top'
                    },
                ]
            },
            {
                name: 'Language',
                type: 'select',
                options: {"English": "en"},
                value: 'en'
            }
        ]
    },
    {
        name: 'Terminal Interface',
        type: 'section',
        children: []
    },
    {
        name: 'Plugins',
        type: 'section',
        children: []
    }
]

let setConfig = baseConfig;

if (localStorage.getItem('config')) {
    setConfig = JSON.parse(localStorage.getItem('config') || '[]');
}

const showTextInNavbar = writable(true);
const navbarPosition = writable('top');
const configStore = writable(baseConfig);

configStore.subscribe(value => {
    // find out which config has changed and what the new value is and store that question is the key and the value is the new value
    const oldConfig = JSON.parse(localStorage.getItem('config') || '[]');
    localStorage.setItem('config', JSON.stringify(value));

    // check if the config has changed
    let changed = {}
    if (JSON.stringify(oldConfig) !== JSON.stringify(value)) {
        function findChanges(oldConfig: any[], newConfig: any[]) {
            for (let i = 0; i < newConfig.length; i++) {
                if (newConfig[i].type === 'section') {
                    findChanges(oldConfig[i].children, newConfig[i].children);
                } else {
                    if (oldConfig[i].value !== newConfig[i].value) {
                        changed[newConfig[i].name] = newConfig[i].value;
                    }
                }
            }
        }
        findChanges(oldConfig, value);
        if (changed['Theme']) {
            document.documentElement.classList.forEach((className) => {
                document.documentElement.classList.remove(className);
            });
            document.documentElement.classList.add(changed['Theme']);
        } else if (changed['Show text in navbar'] !== undefined) {
            console.log('show text in navbar', changed['Show text in navbar']);
            showTextInNavbar.set(changed['Show text in navbar']);
        } else if (changed['Navbar position']) {
            navbarPosition.set(changed['Navbar position']);
        }
    }

});

configStore.set(setConfig);



export { configStore, showTextInNavbar, navbarPosition };
