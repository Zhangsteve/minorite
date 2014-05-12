<?php

use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\DependencyInjection\Container;
use Symfony\Component\DependencyInjection\Exception\InactiveScopeException;
use Symfony\Component\DependencyInjection\Exception\InvalidArgumentException;
use Symfony\Component\DependencyInjection\Exception\LogicException;
use Symfony\Component\DependencyInjection\Exception\RuntimeException;
use Symfony\Component\DependencyInjection\ParameterBag\ParameterBag;

/**
 * ServiceContainer
 *
 * This class has been auto-generated
 * by the Symfony Dependency Injection Component.
 */
class ServiceContainer extends Container
{
    /**
     * Constructor.
     */
    public function __construct()
    {
        parent::__construct();
        $this->methodMap = array(
            'user.entity.storage' => 'getUser_Entity_StorageService',
        );
    }

    /**
     * Gets the 'user.entity.storage' service.
     *
     * This service is shared.
     * This method always returns the same instance of the service.
     *
     * @return Mini\User\Entity\UserStorageController A Mini\User\Entity\UserStorageController instance.
     */
    protected function getUser_Entity_StorageService()
    {
        return $this->services['user.entity.storage'] = call_user_func(array('Drupal\\Core\\DependencyInjection\\EntityControllerFactory', 'get'), 'user');
    }
}
