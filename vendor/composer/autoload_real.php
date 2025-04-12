<?php

// autoload_real.php @generated by Composer

class ComposerAutoloaderInit69fb0433e19d98148e443f1e27d1aca0
{
    private static $loader;

    public static function loadClassLoader($class)
    {
        if ('Composer\Autoload\ClassLoader' === $class) {
            require __DIR__ . '/ClassLoader.php';
        }
    }

    /**
     * @return \Composer\Autoload\ClassLoader
     */
    public static function getLoader()
    {
        if (null !== self::$loader) {
            return self::$loader;
        }

        spl_autoload_register(array('ComposerAutoloaderInit69fb0433e19d98148e443f1e27d1aca0', 'loadClassLoader'), true, true);
        self::$loader = $loader = new \Composer\Autoload\ClassLoader(\dirname(__DIR__));
        spl_autoload_unregister(array('ComposerAutoloaderInit69fb0433e19d98148e443f1e27d1aca0', 'loadClassLoader'));

        require __DIR__ . '/autoload_static.php';
        call_user_func(\Composer\Autoload\ComposerStaticInit69fb0433e19d98148e443f1e27d1aca0::getInitializer($loader));

        $loader->register(true);

        return $loader;
    }
}
